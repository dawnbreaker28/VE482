/*	$NetBSD: ex_global.c,v 1.4 2011/03/21 14:53:03 tnozaki Exp $ */

/*-
 * Copyright (c) 1992, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1992, 1993, 1994, 1995, 1996
 *	Keith Bostic.  All rights reserved.
 *
 * See the LICENSE file for redistribution information.
 */

#include "config.h"

#ifndef lint
static const char sccsid[] = "Id: ex_global.c,v 10.30 2001/06/25 15:19:16 skimo Exp (Berkeley) Date: 2001/06/25 15:19:16";
#endif /* not lint */

#include <sys/types.h>
#include <sys/queue.h>

#include <bitstring.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/common.h"

enum which {GLOBAL, V};

static int ex_g_setup __P((SCR *, EXCMD *, enum which));

/*
 * ex_global -- [line [,line]] g[lobal][!] /pattern/ [commands]
 *	Exec on lines matching a pattern.
 *
 * PUBLIC: int ex_global __P((SCR *, EXCMD *));
 */
int
ex_global(SCR *sp, EXCMD *cmdp)
{
	return (ex_g_setup(sp,
	    cmdp, FL_ISSET(cmdp->iflags, E_C_FORCE) ? V : GLOBAL));
}

/*
 * ex_v -- [line [,line]] v /pattern/ [commands]
 *	Exec on lines not matching a pattern.
 *
 * PUBLIC: int ex_v __P((SCR *, EXCMD *));
 */
int
ex_v(SCR *sp, EXCMD *cmdp)
{
	return (ex_g_setup(sp, cmdp, V));
}

/*
 * ex_g_setup --
 *	Ex global and v commands.
 */
static int
ex_g_setup(SCR *sp, EXCMD *cmdp, enum which cmd)
{
	CHAR_T *ptrn, *p, *t;
	EXCMD *ecp;
	MARK myabs;
	RANGE *rp;
	busy_t btype;
	db_recno_t start, end;
	regex_t *re;
	regmatch_t match[1];
	size_t len;
	int cnt, delim, eval;
	CHAR_T *dbp;

	NEEDFILE(sp, cmdp);

	if (F_ISSET(sp, SC_EX_GLOBAL)) {
		msgq_wstr(sp, M_ERR, cmdp->cmd->name,
	"124|The %s command can't be used as part of a global or v command");
		return (1);
	}

	/*
	 * Skip leading white space.  Historic vi allowed any non-alphanumeric
	 * to serve as the global command delimiter.
	 */
	if (cmdp->argc == 0)
		goto usage;
	for (p = cmdp->argv[0]->bp; ISBLANK(*p); ++p);
	if (*p == '\0' || ISALNUM((UCHAR_T)*p) ||
	    *p == '\\' || *p == '|' || *p == '\n') {
usage:		ex_emsg(sp, cmdp->cmd->usage, EXM_USAGE);
		return (1);
	}
	delim = *p++;

	/*
	 * Get the pattern string, toss escaped characters.
	 *
	 * QUOTING NOTE:
	 * Only toss an escaped character if it escapes a delimiter.
	 */
	for (ptrn = t = p;;) {
		if (p[0] == '\0' || p[0] == delim) {
			if (p[0] == delim)
				++p;
			/*
			 * !!!
			 * Nul terminate the pattern string -- it's passed
			 * to regcomp which doesn't understand anything else.
			 */
			*t = L('\0');
			break;
		}
		if (p[0] == L('\\')) {
			if (p[1] == delim)
				++p;
			else if (p[1] == L('\\'))
				*t++ = *p++;
		}
		*t++ = *p++;
	}

	/* If the pattern string is empty, use the last one. */
	if (*ptrn == L('\0')) {
		if (sp->re == NULL) {
			ex_emsg(sp, NULL, EXM_NOPREVRE);
			return (1);
		}

		/* Re-compile the RE if necessary. */
		if (!F_ISSET(sp, SC_RE_SEARCH) &&
		    re_compile(sp, sp->re, sp->re_len,
		    NULL, NULL, &sp->re_c, SEARCH_CSEARCH | SEARCH_MSG))
			return (1);
	} else {
		/* Compile the RE. */
		if (re_compile(sp, ptrn, t - ptrn, &sp->re,
		    &sp->re_len, &sp->re_c, SEARCH_CSEARCH | SEARCH_MSG))
			return (1);

		/*
		 * Set saved RE.  Historic practice is that globals set
		 * direction as well as the RE.
		 */
		sp->searchdir = FORWARD;
	}
	re = &sp->re_c;

	/* The global commands always set the previous context mark. */
	myabs.lno = sp->lno;
	myabs.cno = sp->cno;
	if (mark_set(sp, ABSMARK1, &myabs, 1))
		return (1);

	/* Get an EXCMD structure. */
	CALLOC_RET(sp, ecp, EXCMD *, 1, sizeof(EXCMD));
	CIRCLEQ_INIT(&ecp->rq);

	/*
	 * Get a copy of the command string; the default command is print.
	 * Don't worry about a set of <blank>s with no command, that will
	 * default to print in the ex parser.  We need to have two copies
	 * because the ex parser may step on the command string when it's
	 * parsing it.
	 */
	if ((len = cmdp->argv[0]->len - (p - cmdp->argv[0]->bp)) == 0) {
		p = __UNCONST(L("p"));
		len = 1;
	}

	MALLOC_RET(sp, ecp->cp, CHAR_T *, (len * 2) * sizeof(CHAR_T));
	ecp->o_cp = ecp->cp;
	ecp->o_clen = len;
	MEMCPYW(ecp->cp + len, p, len);
	ecp->range_lno = OOBLNO;
	FL_SET(ecp->agv_flags, cmd == GLOBAL ? AGV_GLOBAL : AGV_V);
	LIST_INSERT_HEAD(&sp->wp->ecq, ecp, q);

	/*
	 * For each line...  The semantics of global matching are that we first
	 * have to decide which lines are going to get passed to the command,
	 * and then pass them to the command, ignoring other changes.  There's
	 * really no way to do this in a single pass, since arbitrary line
	 * creation, deletion and movement can be done in the ex command.  For
	 * example, a good vi clone test is ":g/X/mo.-3", or "g/X/.,.+1d".
	 * What we do is create linked list of lines that are tracked through
	 * each ex command.  There's a callback routine which the DB interface
	 * routines call when a line is created or deleted.  This doesn't help
	 * the layering much.
	 */
	btype = BUSY_ON;
	cnt = INTERRUPT_CHECK;
	for (start = cmdp->addr1.lno,
	    end = cmdp->addr2.lno; start <= end; ++start) {
		if (cnt-- == 0) {
			if (INTERRUPTED(sp)) {
				LIST_REMOVE(ecp, q);
				free(ecp->cp);
				free(ecp);
				break;
			}
			search_busy(sp, btype);
			btype = BUSY_UPDATE;
			cnt = INTERRUPT_CHECK;
		}
		if (db_get(sp, start, DBG_FATAL, &dbp, &len))
			return (1);
		match[0].rm_so = 0;
		match[0].rm_eo = len;
		switch (eval =
		    regexec(&sp->re_c, dbp, 0, match, REG_STARTEND)) {
		case 0:
			if (cmd == V)
				continue;
			break;
		case REG_NOMATCH:
			if (cmd == GLOBAL)
				continue;
			break;
		default:
			re_error(sp, eval, &sp->re_c);
			break;
		}

		/* If follows the last entry, extend the last entry's range. */
		if ((rp = ecp->rq.cqh_last) != (void *)&ecp->rq &&
		    rp->stop == start - 1) {
			++rp->stop;
			continue;
		}

		/* Allocate a new range, and append it to the list. */
		CALLOC(sp, rp, RANGE *, 1, sizeof(RANGE));
		if (rp == NULL)
			return (1);
		rp->start = rp->stop = start;
		CIRCLEQ_INSERT_TAIL(&ecp->rq, rp, q);
	}
	search_busy(sp, BUSY_OFF);
	return (0);
}

/*
 * ex_g_insdel --
 *	Update the ranges based on an insertion or deletion.
 *
 * PUBLIC: int ex_g_insdel __P((SCR *, lnop_t, db_recno_t));
 */
int
ex_g_insdel(SCR *sp, lnop_t op, db_recno_t lno)
{
	EXCMD *ecp;
	RANGE *nrp, *rp;

	/* All insert/append operations are done as inserts. */
	if (op == LINE_APPEND)
		abort();

	if (op == LINE_RESET)
		return (0);

	for (ecp = sp->wp->ecq.lh_first; ecp != NULL; ecp = ecp->q.le_next) {
		if (!FL_ISSET(ecp->agv_flags, AGV_AT | AGV_GLOBAL | AGV_V))
			continue;
		for (rp = ecp->rq.cqh_first; rp != (void *)&ecp->rq; rp = nrp) {
			nrp = rp->q.cqe_next;

			/* If range less than the line, ignore it. */
			if (rp->stop < lno)
				continue;
			
			/*
			 * If range greater than the line, decrement or
			 * increment the range.
			 */
			if (rp->start > lno) {
				if (op == LINE_DELETE) {
					--rp->start;
					--rp->stop;
				} else {
					++rp->start;
					++rp->stop;
				}
				continue;
			}

			/*
			 * Lno is inside the range, decrement the end point
			 * for deletion, and split the range for insertion.
			 * In the latter case, since we're inserting a new
			 * element, neither range can be exhausted.
			 */
			if (op == LINE_DELETE) {
				if (rp->start > --rp->stop) {
					CIRCLEQ_REMOVE(&ecp->rq, rp, q);
					free(rp);
				}
			} else {
				CALLOC_RET(sp, nrp, RANGE *, 1, sizeof(RANGE));
				nrp->start = lno + 1;
				nrp->stop = rp->stop + 1;
				rp->stop = lno - 1;
				CIRCLEQ_INSERT_AFTER(&ecp->rq, rp, nrp, q);
				rp = nrp;
			}
		}

		/*
		 * If the command deleted/inserted lines, the cursor moves to
		 * the line after the deleted/inserted line.
		 */
		ecp->range_lno = lno;
	}
	return (0);
}

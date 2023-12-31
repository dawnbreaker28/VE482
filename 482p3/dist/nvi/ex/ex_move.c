/*	$NetBSD: ex_move.c,v 1.2 2012/01/27 16:41:22 christos Exp $ */

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
static const char sccsid[] = "Id: ex_move.c,v 10.15 2001/06/25 15:19:17 skimo Exp (Berkeley) Date: 2001/06/25 15:19:17";
#endif /* not lint */

#include <sys/types.h>
#include <sys/queue.h>

#include <bitstring.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"

/*
 * ex_copy -- :[line [,line]] co[py] line [flags]
 *	Copy selected lines.
 *
 * PUBLIC: int ex_copy __P((SCR *, EXCMD *));
 */
int
ex_copy(SCR *sp, EXCMD *cmdp)
{
	CB cb;
	MARK fm1, fm2, m, tm;
	db_recno_t cnt;
	int rval;

	rval = 0;

	NEEDFILE(sp, cmdp);

	/*
	 * It's possible to copy things into the area that's being
	 * copied, e.g. "2,5copy3" is legitimate.  Save the text to
	 * a cut buffer.
	 */
	fm1 = cmdp->addr1;
	fm2 = cmdp->addr2;
	memset(&cb, 0, sizeof(cb));
	CIRCLEQ_INIT(&cb.textq);
	for (cnt = fm1.lno; cnt <= fm2.lno; ++cnt)
		if (cut_line(sp, cnt, 0, ENTIRE_LINE, &cb)) {
			rval = 1;
			goto err;
		}
	cb.flags |= CB_LMODE;

	/* Put the text into place. */
	tm.lno = cmdp->lineno;
	tm.cno = 0;
	if (put(sp, &cb, NULL, &tm, &m, 1))
		rval = 1;
	else {
		/*
		 * Copy puts the cursor on the last line copied.  The cursor
		 * returned by the put routine is the first line put, not the
		 * last, because that's the historic semantic of vi.
		 */
		cnt = (fm2.lno - fm1.lno) + 1;
		sp->lno = m.lno + (cnt - 1);
		sp->cno = 0;
	}
err:	text_lfree(&cb.textq);
	return (rval);
}

/*
 * ex_move -- :[line [,line]] mo[ve] line
 *	Move selected lines.
 *
 * PUBLIC: int ex_move __P((SCR *, EXCMD *));
 */
int
ex_move(SCR *sp, EXCMD *cmdp)
{
	LMARK *lmp;
	MARK fm1, fm2;
	db_recno_t cnt, diff, fl, tl, mfl, mtl;
	size_t blen, len;
	int mark_reset;
	CHAR_T *bp;
	CHAR_T *p;

	NEEDFILE(sp, cmdp);

	/*
	 * It's not possible to move things into the area that's being
	 * moved.
	 */
	fm1 = cmdp->addr1;
	fm2 = cmdp->addr2;
	if (cmdp->lineno >= fm1.lno && cmdp->lineno <= fm2.lno) {
		msgq(sp, M_ERR, "139|Destination line is inside move range");
		return (1);
	}

	/*
	 * Log the positions of any marks in the to-be-deleted lines.  This
	 * has to work with the logging code.  What happens is that we log
	 * the old mark positions, make the changes, then log the new mark
	 * positions.  Then the marks end up in the right positions no matter
	 * which way the log is traversed.
	 *
	 * XXX
	 * Reset the MARK_USERSET flag so that the log can undo the mark.
	 * This isn't very clean, and should probably be fixed.
	 */
	fl = fm1.lno;
	tl = cmdp->lineno;

	/* Log the old positions of the marks. */
	mark_reset = 0;
	for (lmp = sp->ep->marks.lh_first; lmp != NULL; lmp = lmp->q.le_next)
		if (lmp->name != ABSMARK1 &&
		    lmp->lno >= fl && lmp->lno <= tl) {
			mark_reset = 1;
			F_CLR(lmp, MARK_USERSET);
			(void)log_mark(sp, lmp);
		}

	/* Get memory for the copy. */
	GET_SPACE_RETW(sp, bp, blen, 256);

	/* Move the lines. */
	diff = (fm2.lno - fm1.lno) + 1;
	if (tl > fl) {				/* Destination > source. */
		mfl = tl - diff;
		mtl = tl;
		for (cnt = diff; cnt--;) {
			if (db_get(sp, fl, DBG_FATAL, &p, &len))
				return (1);
			BINC_RETW(sp, bp, blen, len);
			MEMCPYW(bp, p, len);
			if (db_append(sp, 1, tl, bp, len))
				return (1);
			if (mark_reset)
				for (lmp = sp->ep->marks.lh_first;
				    lmp != NULL; lmp = lmp->q.le_next)
					if (lmp->name != ABSMARK1 &&
					    lmp->lno == fl)
						lmp->lno = tl + 1;
			if (db_delete(sp, fl))
				return (1);
		}
	} else {				/* Destination < source. */
		mfl = tl;
		mtl = tl + diff;
		for (cnt = diff; cnt--;) {
			if (db_get(sp, fl, DBG_FATAL, &p, &len))
				return (1);
			BINC_RETW(sp, bp, blen, len);
			MEMCPYW(bp, p, len);
			if (db_append(sp, 1, tl++, bp, len))
				return (1);
			if (mark_reset)
				for (lmp = sp->ep->marks.lh_first;
				    lmp != NULL; lmp = lmp->q.le_next)
					if (lmp->name != ABSMARK1 &&
					    lmp->lno == fl)
						lmp->lno = tl;
			++fl;
			if (db_delete(sp, fl))
				return (1);
		}
	}
	FREE_SPACEW(sp, bp, blen);

	sp->lno = tl;				/* Last line moved. */
	sp->cno = 0;

	/* Log the new positions of the marks. */
	if (mark_reset)
		for (lmp = sp->ep->marks.lh_first;
		    lmp != NULL; lmp = lmp->q.le_next)
			if (lmp->name != ABSMARK1 &&
			    lmp->lno >= mfl && lmp->lno <= mtl)
				(void)log_mark(sp, lmp);


	sp->rptlines[L_MOVED] += diff;
	return (0);
}

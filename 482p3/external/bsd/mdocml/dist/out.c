/*	$Vendor-Id: out.c,v 1.30 2011/01/05 15:37:23 kristaps Exp $ */
/*
 * Copyright (c) 2009, 2010 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mandoc.h"
#include "out.h"

static	void	tblcalc_data(struct rofftbl *, struct roffcol *,
			const struct tbl *, const struct tbl_dat *);
static	void	tblcalc_literal(struct rofftbl *, struct roffcol *,
			const struct tbl_dat *);
static	void	tblcalc_number(struct rofftbl *, struct roffcol *,
			const struct tbl *, const struct tbl_dat *);

/* 
 * Convert a `scaling unit' to a consistent form, or fail.  Scaling
 * units are documented in groff.7, mdoc.7, man.7.
 */
int
a2roffsu(const char *src, struct roffsu *dst, enum roffscale def)
{
	char		 buf[BUFSIZ], hasd;
	int		 i;
	enum roffscale	 unit;

	if ('\0' == *src)
		return(0);

	i = hasd = 0;

	switch (*src) {
	case ('+'):
		src++;
		break;
	case ('-'):
		buf[i++] = *src++;
		break;
	default:
		break;
	}

	if ('\0' == *src)
		return(0);

	while (i < BUFSIZ) {
		if ( ! isdigit((u_char)*src)) {
			if ('.' != *src)
				break;
			else if (hasd)
				break;
			else
				hasd = 1;
		}
		buf[i++] = *src++;
	}

	if (BUFSIZ == i || (*src && *(src + 1)))
		return(0);

	buf[i] = '\0';

	switch (*src) {
	case ('c'):
		unit = SCALE_CM;
		break;
	case ('i'):
		unit = SCALE_IN;
		break;
	case ('P'):
		unit = SCALE_PC;
		break;
	case ('p'):
		unit = SCALE_PT;
		break;
	case ('f'):
		unit = SCALE_FS;
		break;
	case ('v'):
		unit = SCALE_VS;
		break;
	case ('m'):
		unit = SCALE_EM;
		break;
	case ('\0'):
		if (SCALE_MAX == def)
			return(0);
		unit = SCALE_BU;
		break;
	case ('u'):
		unit = SCALE_BU;
		break;
	case ('M'):
		unit = SCALE_MM;
		break;
	case ('n'):
		unit = SCALE_EN;
		break;
	default:
		return(0);
	}

	/* FIXME: do this in the caller. */
	if ((dst->scale = atof(buf)) < 0)
		dst->scale = 0;
	dst->unit = unit;
	return(1);
}


/*
 * Correctly writes the time in nroff form, which differs from standard
 * form in that a space isn't printed in lieu of the extra %e field for
 * single-digit dates.
 */
void
time2a(time_t t, char *dst, size_t sz)
{
	struct tm	 tm;
	char		 buf[5];
	char		*p;
	size_t		 nsz;

	assert(sz > 1);
	localtime_r(&t, &tm);

	p = dst;
	nsz = 0;

	dst[0] = '\0';

	if (0 == (nsz = strftime(p, sz, "%B ", &tm)))
		return;

	p += (int)nsz;
	sz -= nsz;

	if (0 == strftime(buf, sizeof(buf), "%e, ", &tm))
		return;

	nsz = strlcat(p, buf + (' ' == buf[0] ? 1 : 0), sz);

	if (nsz >= sz)
		return;

	p += (int)nsz;
	sz -= nsz;

	(void)strftime(p, sz, "%Y", &tm);
}


int
a2roffdeco(enum roffdeco *d, const char **word, size_t *sz)
{
	int		 i, j, lim;
	char		 term, c;
	const char	*wp;
	enum roffdeco	 dd;

	*d = DECO_NONE;
	lim = i = 0;
	term = '\0';
	wp = *word;

	switch ((c = wp[i++])) {
	case ('('):
		*d = DECO_SPECIAL;
		lim = 2;
		break;
	case ('F'):
		/* FALLTHROUGH */
	case ('f'):
		*d = 'F' == c ? DECO_FFONT : DECO_FONT;

		switch (wp[i++]) {
		case ('('):
			lim = 2;
			break;
		case ('['):
			term = ']';
			break;
		case ('3'):
			/* FALLTHROUGH */
		case ('B'):
			*d = DECO_BOLD;
			return(i);
		case ('2'):
			/* FALLTHROUGH */
		case ('I'):
			*d = DECO_ITALIC;
			return(i);
		case ('P'):
			*d = DECO_PREVIOUS;
			return(i);
		case ('1'):
			/* FALLTHROUGH */
		case ('R'):
			*d = DECO_ROMAN;
			return(i);
		default:
			i--;
			lim = 1;
			break;
		}
		break;
	case ('k'):
		/* FALLTHROUGH */
	case ('M'):
		/* FALLTHROUGH */
	case ('m'):
		/* FALLTHROUGH */
	case ('*'):
		if ('*' == c)
			*d = DECO_RESERVED;

		switch (wp[i++]) {
		case ('('):
			lim = 2;
			break;
		case ('['):
			term = ']';
			break;
		default:
			i--;
			lim = 1;
			break;
		}
		break;
	case ('h'):
		/* FALLTHROUGH */
	case ('v'):
		/* FALLTHROUGH */
	case ('s'):
		j = 0;
		if ('+' == wp[i] || '-' == wp[i]) {
			i++;
			j = 1;
		}

		switch (wp[i++]) {
		case ('('):
			lim = 2;
			break;
		case ('['):
			term = ']';
			break;
		case ('\''):
			term = '\'';
			break;
		case ('0'):
			j = 1;
			/* FALLTHROUGH */
		default:
			i--;
			lim = 1;
			break;
		}

		if ('+' == wp[i] || '-' == wp[i]) {
			if (j)
				return(i);
			i++;
		} 

		/* Handle embedded numerical subexp or escape. */

		if ('(' == wp[i]) {
			while (wp[i] && ')' != wp[i])
				if ('\\' == wp[i++]) {
					/* Handle embedded escape. */
					*word = &wp[i];
					i += a2roffdeco(&dd, word, sz);
				}

			if (')' == wp[i++])
				break;

			*d = DECO_NONE;
			return(i - 1);
		} else if ('\\' == wp[i]) {
			*word = &wp[++i];
			i += a2roffdeco(&dd, word, sz);
		}

		break;
	case ('['):
		*d = DECO_SPECIAL;
		term = ']';
		break;
	case ('c'):
		*d = DECO_NOSPACE;
		return(i);
	case ('z'):
		*d = DECO_NONE;
		if ('\\' == wp[i]) {
			*word = &wp[++i];
			return(i + a2roffdeco(&dd, word, sz));
		} else
			lim = 1;
		break;
	case ('o'):
		/* FALLTHROUGH */
	case ('w'):
		if ('\'' == wp[i++]) {
			term = '\'';
			break;
		} 
		/* FALLTHROUGH */
	default:
		*d = DECO_SSPECIAL;
		i--;
		lim = 1;
		break;
	}

	assert(term || lim);
	*word = &wp[i];

	if (term) {
		j = i;
		while (wp[i] && wp[i] != term)
			i++;
		if ('\0' == wp[i]) {
			*d = DECO_NONE;
			return(i);
		}

		assert(i >= j);
		*sz = (size_t)(i - j);

		return(i + 1);
	}

	assert(lim > 0);
	*sz = (size_t)lim;

	for (j = 0; wp[i] && j < lim; j++)
		i++;
	if (j < lim)
		*d = DECO_NONE;

	return(i);
}

/*
 * Calculate the abstract widths and decimal positions of columns in a
 * table.  This routine allocates the columns structures then runs over
 * all rows and cells in the table.  The function pointers in "tbl" are
 * used for the actual width calculations.
 */
void
tblcalc(struct rofftbl *tbl, const struct tbl_span *sp)
{
	const struct tbl_dat	*dp;
	const struct tbl_head	*hp;
	struct roffcol		*col;

	/*
	 * Allocate the master column specifiers.  These will hold the
	 * widths and decimal positions for all cells in the column.  It
	 * must be freed and nullified by the caller.
	 */

	assert(NULL == tbl->cols);
	tbl->cols = calloc(sp->tbl->cols, sizeof(struct roffcol));

	hp = sp->head;

	for ( ; sp; sp = sp->next) {
		if (TBL_SPAN_DATA != sp->pos)
			continue;
		/*
		 * Account for the data cells in the layout, matching it
		 * to data cells in the data section.
		 */
		for (dp = sp->first; dp; dp = dp->next) {
			if (NULL == dp->layout)
				continue;
			col = &tbl->cols[dp->layout->head->ident];
			tblcalc_data(tbl, col, sp->tbl, dp);
		}
	}

	/* 
	 * Calculate width of the spanners.  These get one space for a
	 * vertical line, two for a double-vertical line. 
	 */

	for ( ; hp; hp = hp->next) {
		col = &tbl->cols[hp->ident];
		switch (hp->pos) {
		case (TBL_HEAD_VERT):
			col->width = (*tbl->len)(1, tbl->arg);
			break;
		case (TBL_HEAD_DVERT):
			col->width = (*tbl->len)(2, tbl->arg);
			break;
		default:
			break;
		}
	}
}

static void
tblcalc_data(struct rofftbl *tbl, struct roffcol *col,
		const struct tbl *tp, const struct tbl_dat *dp)
{
	size_t		 sz;

	/* Branch down into data sub-types. */

	switch (dp->layout->pos) {
	case (TBL_CELL_HORIZ):
		/* FALLTHROUGH */
	case (TBL_CELL_DHORIZ):
		sz = (*tbl->len)(1, tbl->arg);
		if (col->width < sz)
			col->width = sz;
		break;
	case (TBL_CELL_LONG):
		/* FALLTHROUGH */
	case (TBL_CELL_CENTRE):
		/* FALLTHROUGH */
	case (TBL_CELL_LEFT):
		/* FALLTHROUGH */
	case (TBL_CELL_RIGHT):
		tblcalc_literal(tbl, col, dp);
		break;
	case (TBL_CELL_NUMBER):
		tblcalc_number(tbl, col, tp, dp);
		break;
	default:
		abort();
		/* NOTREACHED */
	}
}

static void
tblcalc_literal(struct rofftbl *tbl, struct roffcol *col,
		const struct tbl_dat *dp)
{
	size_t		 sz, bufsz, spsz;

	/* 
	 * Calculate our width and use the spacing, with a minimum
	 * spacing dictated by position (centre, e.g,. gets a space on
	 * either side, while right/left get a single adjacent space).
	 */

	sz = bufsz = spsz = 0;
	if (dp->string)
		sz = (*tbl->slen)(dp->string, tbl->arg);

	assert(dp->layout);
	switch (dp->layout->pos) {
	case (TBL_CELL_LONG):
		/* FALLTHROUGH */
	case (TBL_CELL_CENTRE):
		bufsz = (*tbl->len)(2, tbl->arg);
		break;
	default:
		bufsz = (*tbl->len)(1, tbl->arg);
		break;
	}

	if (dp->layout->spacing) {
		spsz = (*tbl->len)(dp->layout->spacing, tbl->arg);
		bufsz = bufsz > spsz ? bufsz : spsz;
	}

	sz += bufsz;
	if (col->width < sz)
		col->width = sz;
}

static void
tblcalc_number(struct rofftbl *tbl, struct roffcol *col,
		const struct tbl *tp, const struct tbl_dat *dp)
{
	int 		 i;
	size_t		 sz, psz, ssz, d;
	char		*cp;
	const char	*str;
	char		 buf[2];

	/* TODO: use spacing modifier. */

	/*
	 * First calculate number width and decimal place (last + 1 for
	 * no-decimal numbers).  If the stored decimal is subsequent
	 * ours, make our size longer by that difference
	 * (right-"shifting"); similarly, if ours is subsequent the
	 * stored, then extend the stored size by the difference.
	 * Finally, re-assign the stored values.
	 */

	str = "";
	if (dp->string)
		str = dp->string;

	sz = (*tbl->slen)(str, tbl->arg);

	buf[0] = tp->decimal;
	buf[1] = '\0';

	psz = (*tbl->slen)(buf, tbl->arg);

	if (NULL != (cp = strchr(str, tp->decimal))) {
		buf[1] = '\0';
		for (ssz = 0, i = 0; cp != &str[i]; i++) {
			buf[0] = str[i];
			ssz += (*tbl->slen)(buf, tbl->arg);
		}
		d = ssz + psz;
	} else
		d = sz + psz;

	/* Padding. */

	sz += (*tbl->len)(2, tbl->arg);
	d += (*tbl->len)(1, tbl->arg);

	/* Adjust the settings for this column. */

	if (col->decimal > d) {
		sz += col->decimal - d;
		d = col->decimal;
	} else
		col->width += d - col->decimal;

	if (sz > col->width)
		col->width = sz;
	if (d > col->decimal)
		col->decimal = d;
}



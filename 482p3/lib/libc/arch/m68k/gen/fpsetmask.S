/*	$NetBSD: fpsetmask.S,v 1.7 2002/01/13 21:45:44 thorpej Exp $	*/

/*
 * Written by Charles M. Hannum, Apr 9, 1995
 * Public Domain.
 */

#include <machine/asm.h>

#ifdef WEAK_ALIAS
WEAK_ALIAS(fpsetmask, _fpsetmask)
ENTRY(_fpsetmask)
#else
ENTRY(fpsetmask)
#endif
	movel %d2,%sp@-
	fmovel %fpcr,%d1
	movel %sp@(8),%d2
	bfextu %d1{#18:#5},%d0
	bfins %d2,%d1{#18:#5}
	movel %sp@+,%d2
	fmovel %d1,%fpcr
	rts

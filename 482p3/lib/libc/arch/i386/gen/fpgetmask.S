/*	$NetBSD: fpgetmask.S,v 1.4 2002/01/13 21:45:42 thorpej Exp $	*/

/*
 * Written by J.T. Conklin, Apr 4, 1995
 * Public domain.
 */

#include <machine/asm.h>

#ifdef WEAK_ALIAS
WEAK_ALIAS(fpgetmask, _fpgetmask)
ENTRY(_fpgetmask)
#else
ENTRY(fpgetmask)
#endif
	subl $4,%esp
	fnstcw (%esp)
	movl (%esp),%eax
	notl %eax
	andl $63,%eax
	addl $4,%esp
	ret

/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 */

#include <machine/asm.h>

RCSID("$NetBSD: s_floor.S,v 1.8 2003/07/26 19:25:02 salo Exp $")

ENTRY(floor)
#ifdef __i386__
	pushl	%ebp
	movl	%esp,%ebp
	subl	$8,%esp

	fstcw	-4(%ebp)		/* store fpu control word */
	movw	-4(%ebp),%dx
	orw	$0x0400,%dx		/* round towards -oo */
	andw	$0xf7ff,%dx
	movw	%dx,-8(%ebp)
	fldcw	-8(%ebp)		/* load modfied control word */

	fldl	8(%ebp);		/* round */
	frndint

	fldcw	-4(%ebp)		/* restore original control word */

	leave
#else
	movsd	%xmm0, -8(%rsp)
	fstcw	-12(%rsp)
	movw	-12(%rsp),%dx
	orw	$0x0400,%dx
	andw	$0xf7ff,%dx
	movw	%dx,-16(%rsp)
	fldcw	-16(%rsp)
	fldl	-8(%rsp)
	frndint
	fldcw	-12(%rsp)
	fstpl	-8(%rsp)
	movsd	-8(%rsp),%xmm0
#endif
	ret

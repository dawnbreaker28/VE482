/*	$NetBSD: compat_setjmp.S,v 1.1 2006/03/09 16:20:55 christos Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <machine/asm.h>

#if defined(LIBC_SCCS) && !defined(lint)
#if 0
	RCSID("from: @(#)setjmp.s	5.1 (Berkeley) 5/12/90")
#else
	RCSID("$NetBSD: compat_setjmp.S,v 1.1 2006/03/09 16:20:55 christos Exp $")
#endif
#endif /* LIBC_SCCS and not lint */

/*
 * C library -- setjmp, longjmp
 *
 *	longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	setjmp(a)
 * by restoring registers from the stack,
 * and a struct sigcontext, see <signal.h>
 */

ENTRY(setjmp)
	lea	%sp@(-12),%sp	/* space for sigstack args/rvals */
	clrl	%sp@		/* don't change it... */
	movl	%sp,%sp@(4)	/* ...but return the current val */
	jbsr	PIC_PLT(_C_LABEL(__sigaltstack14))
				/* note: flags returned in sp@(8) */
	clrl	%sp@		/* don't change mask, just return */
	jbsr	PIC_PLT(_C_LABEL(sigblock)) /*  old value */
	movl	%sp@(8),%d1	/* old flags value */
	andl	#1,%d1		/* extract onstack flag */
	lea	%sp@(12),%sp
	movl	%sp@(4),%a0	/* save area pointer */
	movl	%d1,%a0@+	/* save old onstack value */
	movl	%d0,%a0@+	/* save old signal mask */
	lea	%sp@(4),%a1	/* adjust saved SP since we won't rts */
	movl	%a1,%a0@+	/* save old SP */
	movl	%a6,%a0@+	/* save old FP */
	clrl	%a0@+		/* no AP */
	movl	%sp@,%a0@+	/* save old PC */
	clrl	%a0@+		/* clean PS */
	moveml	#0x3CFC,%a0@	/* save remaining non-scratch regs */
	clrl	%d0		/* return 0 */
	rts

ENTRY(longjmp)
	movl	%sp@(4),%a0	/* save area pointer */
	tstl	%a0@(8)		/* ensure non-zero SP */
	jeq	botch		/* oops! */
	movl	%sp@(8),%d0	/* grab return value */
	jne	ok		/* non-zero ok */
	moveq	#1,%d0		/* else make non-zero */
ok:
	moveml	%a0@(28),#0x3CFC /* restore non-scratch regs */
	movl	%a0,%sp@-	 /* let sigreturn */
	jbsr	PIC_PLT(_C_LABEL(sigreturn)) /*  finish for us */

botch:
	jbsr	PIC_PLT(_C_LABEL(longjmperror))
	stop	#0

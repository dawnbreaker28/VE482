/*	$NetBSD: sigtypes.h,v 1.10 2012/02/19 21:07:00 rmind Exp $	*/

/*
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *
 *	@(#)signal.h	8.4 (Berkeley) 5/4/95
 */

#ifndef	_SYS_SIGTYPES_H_
#define	_SYS_SIGTYPES_H_

/*
 * This header file defines various signal-related types.  We also keep
 * the macros to manipulate sigset_t here, to encapsulate knowledge of
 * its internals.
 */

#include <sys/featuretest.h>
#include <machine/int_types.h>
#include <machine/ansi.h>

#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_NETBSD_SOURCE)
typedef unsigned long sigset_t;

/*
 * Macro for manipulating signal masks.
 */
#ifndef __minix
#define __sigmask(n)		(1 << (((unsigned int)(n) - 1)))
#else /* __minix */
#define __sigmask(n)		(1 << (unsigned int)(n))
#endif /* !__minix */ 
#define __sigaddset(s, n)					\
	do {							\
		*(s) = *(unsigned long *)(s) | __sigmask(n);	\
	} while(0)
#define __sigdelset(s, n)					\
	do {							\
		*(s) = *(unsigned long *)(s) & ~__sigmask(n);	\
	} while (0)

#define __sigismember(s, n)	(((*(const unsigned long *)(s)) & __sigmask(n)) != 0)
#define __sigemptyset(s)	(*(unsigned long *)(s) = 0)
#define __sigsetequal(s1, s2)	(*(unsigned long *)(s1) = *(unsigned long *)(s2))
#define __sigfillset(s)		(*(long *)(s) = -1L)
#define __sigplusset(s, t)						\
	do {								\
		*(t) = *(unsigned long *)(t) | *(unsigned long *)(s);	\
	} while (0)
#define __sigminusset(s, t)					\
	do {							\
		*(t) = *(unsigned long *)(t) & ~*(unsigned long *)(s);	\
	} while (0)
#define __sigandset(s, t)					\
	do {							\
		*(t) = *(unsigned long *)(t) & *(unsigned long *)(s);	\
	} while (0)

#if (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) || \
    (_XOPEN_SOURCE - 0) >= 500 || defined(_NETBSD_SOURCE)
typedef struct
#if defined(_NETBSD_SOURCE)
               sigaltstack
#endif /* _NETBSD_SOURCE */
			   {
	void	*ss_sp;			/* signal stack base */
	size_t	ss_size;		/* signal stack length */
	int	ss_flags;		/* SS_DISABLE and/or SS_ONSTACK */
} stack_t;

#endif /* _XOPEN_SOURCE_EXTENDED || XOPEN_SOURCE >= 500 || _NETBSD_SOURCE */

#endif	/* _POSIX_C_SOURCE || _XOPEN_SOURCE || ... */

#endif	/* !_SYS_SIGTYPES_H_ */

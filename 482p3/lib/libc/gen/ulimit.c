/*	$NetBSD: ulimit.c,v 1.3 2008/04/28 20:22:59 martin Exp $	*/

/*-
 * Copyright (c) 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: ulimit.c,v 1.3 2008/04/28 20:22:59 martin Exp $");
#endif /* LIBC_SCCS and not lint */

#include <sys/resource.h>
#include <errno.h>
#include <stdarg.h>
#include <ulimit.h>

long int
ulimit(int cmd, ...)
{
	va_list ap;
	struct rlimit rlimit;
#ifndef __minix
	long int new_limit, result;
#else
	long int result;
#endif

	va_start(ap, cmd);

	result = -1L;
	switch (cmd) {
	case UL_GETFSIZE:
		if (getrlimit(RLIMIT_FSIZE, &rlimit) == 0)
			result = (long int)(rlimit.rlim_cur / 512);
		break;
#ifndef __minix
	case UL_SETFSIZE:
		new_limit = va_arg(ap, long int);
		rlimit.rlim_cur = rlimit.rlim_max = (rlim_t)new_limit * 512;
		if (setrlimit(RLIMIT_FSIZE, &rlimit) == 0)
			result = new_limit;
		break;
#endif
	default:
		errno = EINVAL;
	}

	va_end(ap);

	return (result);
}

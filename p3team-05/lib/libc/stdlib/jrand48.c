/*	$NetBSD: jrand48.c,v 1.8 2005/06/12 05:21:28 lukem Exp $	*/

/*
 * Copyright (c) 1993 Martin Birgmeier
 * All rights reserved.
 *
 * You may redistribute unmodified or modified versions of this source
 * code provided that the above copyright notice and this and the
 * following conditions are retained.
 *
 * This software is provided ``as is'', and comes with no warranties
 * of any kind. I shall in no event be liable for anything that happens
 * to anyone/anything when using this software.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: jrand48.c,v 1.8 2005/06/12 05:21:28 lukem Exp $");
#endif /* LIBC_SCCS and not lint */

#include "namespace.h"

#include <assert.h>

#include "rand48.h"

#ifdef __weak_alias
__weak_alias(jrand48,_jrand48)
#endif

long
jrand48(unsigned short xseed[3])
{

	_DIAGASSERT(xseed != NULL);

	__dorand48(xseed);
	return ((long) xseed[2] << 16) + (long) xseed[1];
}

/*	$NetBSD: bcmp.S,v 1.2 2003/10/06 05:30:21 matt Exp $	*/

/*	$OpenBSD: bcmp.S,v 1.3 2001/06/04 23:14:02 mickey Exp $	*/

/*
 * Copyright 1996 1995 by Open Software Foundation, Inc.   
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 */
/*
 *  (c) Copyright 1988 HEWLETT-PACKARD COMPANY
 *
 *  To anyone who acknowledges that this file is provided "AS IS"
 *  without any express or implied warranty:
 *      permission to use, copy, modify, and distribute this file
 *  for any purpose is hereby granted without fee, provided that
 *  the above copyright notice and this notice appears in all
 *  copies, and that the name of Hewlett-Packard Company not be
 *  used in advertising or publicity pertaining to distribution
 *  of the software without specific, written prior permission.
 *  Hewlett-Packard Company makes no representations about the
 *  suitability of this software for any purpose.
 */
/*
 * Copyright (c) 1990,1991,1994 The University of Utah and
 * the Computer Systems Laboratory (CSL).  All rights reserved.
 *
 * THE UNIVERSITY OF UTAH AND CSL PROVIDE THIS SOFTWARE IN ITS "AS IS"
 * CONDITION, AND DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
 * WHATSOEVER RESULTING FROM ITS USE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 *
 * 	Utah Hdr: movc.s 1.26 94/12/14
 */

#include <machine/asm.h>

#ifdef SYSLIBC_SCCS
	.text
	.asciz "$OpenBSD: bcmp.S,v 1.3 2001/06/04 23:14:02 mickey Exp $"
	.align	4
#endif

/*
 * int
 * bcmp(src, dst, count)
 *	vaddr_t	src;
 *	vaddr_t	dst;
 *	size_t	count;
 */
LEAF_ENTRY(bcmp)
        comb,>= %r0,%arg2,$bcmp_exit
	copy	%t1,%t2

$bcmp_loop:
	ldbs,ma	1(%arg0),%t1
	ldbs,ma	1(%arg1),%t2
	comb,<>,n %t1,%t2,$bcmp_exit
	addib,<> -1,%arg2,$bcmp_loop
	nop

$bcmp_exit:
	bv	0(%r2)
	sub	%t1,%t2,%ret0

EXIT(bcmp)


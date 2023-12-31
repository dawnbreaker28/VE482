/*	$NetBSD: atomic_dec_32.S,v 1.3 2012/08/31 23:41:52 matt Exp $	*/
/*-
 * Copyright (c) 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Matt Thomas <matt@3am-software.com>
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

#include "atomic_op_asm.h"

#ifdef _ARM_ARCH_6

ENTRY_NP(_atomic_dec_32)
	mov	r2, r0			/* need r0 for return value */
1:	ldrex	r0, [r2]		/* load old value (return value) */
	sub	r1, r0, #1		/* calculate new value */
	strex	r3, r1, [r2]		/* try to store */
	cmp	r3, #0			/*   succeed? */
	bne	1b			/*     no, try again? */
#ifdef _ARM_ARCH_7
	dmb
#else
	mcr	p15, 0, ip, c7, c10, 5	/* data memory barrier */
#endif
	RET				/* return new value */
	END(_atomic_dec_32)
ATOMIC_OP_ALIAS(atomic_dec_32,_atomic_dec_32)
ATOMIC_OP_ALIAS(atomic_dec_uint,_atomic_dec_32)
ATOMIC_OP_ALIAS(atomic_dec_ulong,_atomic_dec_32)
ATOMIC_OP_ALIAS(atomic_dec_ptr,_atomic_dec_32)
STRONG_ALIAS(_atomic_dec_uint,_atomic_dec_32)
STRONG_ALIAS(_atomic_dec_ulong,_atomic_dec_32)
STRONG_ALIAS(_atomic_dec_ptr,_atomic_dec_32)

ENTRY_NP(_atomic_dec_32_nv)
	mov	r2, r0			/* need r0 for return value */
1:	ldrex	r0, [r2]		/* load old value */
	sub	r0, r0, #1		/* calculate new value (return value) */
	strex	r1, r0, [r2]		/* try to store */
	cmp	r1, #0			/*   succeed? */
	bne	1b			/*     no, try again? */
#ifdef _ARM_ARCH_7
	dmb
#else
	mcr	p15, 0, ip, c7, c10, 5	/* data memory barrier */
#endif
	RET				/* return new value */
	END(_atomic_dec_32_nv)
ATOMIC_OP_ALIAS(atomic_dec_32_nv,_atomic_dec_32_nv)
ATOMIC_OP_ALIAS(atomic_dec_uint_nv,_atomic_dec_32_nv)
ATOMIC_OP_ALIAS(atomic_dec_ulong_nv,_atomic_dec_32_nv)
ATOMIC_OP_ALIAS(atomic_dec_ptr_nv,_atomic_dec_32_nv)
STRONG_ALIAS(_atomic_dec_uint_nv,_atomic_dec_32_nv)
STRONG_ALIAS(_atomic_dec_ulong_nv,_atomic_dec_32_nv)
STRONG_ALIAS(_atomic_dec_ptr_nv,_atomic_dec_32_nv)

#endif /* _ARM_ARCH_6 */

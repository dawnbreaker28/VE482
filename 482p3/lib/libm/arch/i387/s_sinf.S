/*
 * Written by J.T. Conklin <jtc@NetBSD.org>.
 * Public domain.
 */

#include <machine/asm.h>

#include "abi.h"

RCSID("$NetBSD: s_sinf.S,v 1.5 2003/07/26 19:25:04 salo Exp $")

/* A float's domain isn't large enough to require argument reduction. */
ENTRY(sinf)
	XMM_ONE_ARG_FLOAT_PROLOGUE
	flds	ARG_FLOAT_ONE
	fsin
	XMM_FLOAT_EPILOGUE
	ret

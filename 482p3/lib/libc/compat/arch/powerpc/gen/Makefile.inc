#	$NetBSD: Makefile.inc,v 1.3 2006/06/28 14:46:33 drochner Exp $

# objects built from assembler sources (need lint stubs)
SRCS+=	compat_setjmp.S compat_sigsetjmp.S

# objects built from C sources in compat/gen
SRCS+=	compat_frexp_ieee754.c compat_ldexp_ieee754.c compat_modf_ieee754.c

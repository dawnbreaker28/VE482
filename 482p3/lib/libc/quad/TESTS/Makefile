#	$NetBSD: Makefile,v 1.2 1995/02/27 17:31:26 cgd Exp $
#	@(#)Makefile	8.1 (Berkeley) 6/4/93

all: mul divrem

MUL=	mul.c ../muldi3.c
mul: ${MUL}
	gcc -g -DSPARC_XXX ${MUL} -o $@

DIVREM=	divrem.c ../qdivrem.c
divrem: ${DIVREM}
	gcc -g -DSPARC_XXX ${DIVREM} -o $@

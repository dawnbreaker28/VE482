#	$NetBSD: Makefile.inc,v 1.16 2011/03/26 19:51:42 christos Exp $

# objects built from assembler sources (need lint stubs)
SRCS+=	alloca.S byte_swap_2.S byte_swap_4.S byte_swap_8.S fabs.S \
	flt_rounds.S fpgetmask.S fpgetround.S fpgetsticky.S \
	fpsetmask.S fpsetround.S fpsetsticky.S fpgetprec.S \
	fpsetprec.S

SRCS+=	__setjmp14.S
SRCS+=	_setjmp.S
SRCS+=	__sigsetjmp14.S

SRCS+=	resumecontext.S swapcontext.S

# objects built from C sources
SRCS+=	_lwp.c makecontext.c

# Common ieee754 constants and functions
SRCS+=	infinityf_ieee754.c infinity_ieee754.c
SRCS+=	fpclassifyf_ieee754.c fpclassifyd_ieee754.c
SRCS+=	isfinitef_ieee754.c isfinited_ieee754.c
SRCS+=	isinff_ieee754.c isinfd_ieee754.c
SRCS+=	isnanf_ieee754.c isnand_ieee754.c
SRCS+=	signbitf_ieee754.c signbitd_ieee754.c

SRCS+=	nanf.c infinityl.c
SRCS+=	fpclassifyl.c isfinitel.c isinfl.c isnanl.c signbitl.c

LSRCS.x86_64.gen=\
	Lint__setjmp.c Lint_alloca.c Lint_bswap16.c Lint_bswap32.c \
	Lint_bswap64.c Lint_fabs.c \
	Lint___setjmp14.c Lint___sigsetjmp14.c Lint_flt_rounds.c \
	Lint_fpgetmask.c Lint_fpgetround.c Lint_fpgetsticky.c \
	Lint_fpsetmask.c Lint_fpsetround.c Lint_fpsetsticky.c
LSRCS+=		${LSRCS.x86_64.gen}
DPSRCS+=	${LSRCS.x86_64.gen}
CLEANFILES+=	${LSRCS.x86_64.gen}

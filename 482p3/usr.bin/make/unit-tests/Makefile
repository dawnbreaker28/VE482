# $NetBSD: Makefile,v 1.34 2012/06/19 23:25:53 sjg Exp $
#
# Unit tests for make(1)
# The main targets are:
# 
# all:	run all the tests
# test:	run 'all', capture output and compare to expected results
# accept: move generated output to expected results
#
# Adding a test case.  
# Each feature should get its own set of tests in its own suitably
# named makefile which should be added to SUBFILES to hook it in.
# 

.MAIN: all

UNIT_TESTS:= ${.PARSEDIR}

# Simple sub-makefiles - we run them as a black box
# keep the list sorted.
SUBFILES= \
	comment \
	cond1 \
	error \
	export \
	export-all \
	doterror \
	dotwait \
	forloop \
	forsubst \
	hash \
	misc \
	moderrs \
	modmatch \
	modmisc \
	modorder \
	modts \
	modword \
	phony-end \
	posix \
	qequals \
	sysv \
	ternary \
	unexport \
	unexport-env \
	varcmd

all: ${SUBFILES}

flags.doterror=

# the tests are actually done with sub-makes.
.PHONY: ${SUBFILES}
.PRECIOUS: ${SUBFILES}
${SUBFILES}:
	-@${.MAKE} ${flags.$@:U-k} -f ${UNIT_TESTS}/$@

clean:
	rm -f *.out *.fail *.core

.-include <bsd.obj.mk>

TEST_MAKE?= ${.MAKE}
TOOL_SED?= sed

# ensure consistent results from sort(1)
LC_ALL= C
LANG= C
.export LANG LC_ALL

# The driver.
# We always pretend .MAKE was called 'make' 
# and strip ${.CURDIR}/ from the output
# and replace anything after 'stopped in' with unit-tests
# so the results can be compared.
test:
	@echo "${TEST_MAKE} -f ${MAKEFILE} > ${.TARGET}.out 2>&1"
	@cd ${.OBJDIR} && ${TEST_MAKE} -f ${MAKEFILE} 2>&1 | \
	${TOOL_SED} -e 's,^${TEST_MAKE:T:C/\./\\\./g}:,make:,' \
	-e '/stopped/s, /.*, unit-tests,' \
	-e 's,${.CURDIR:C/\./\\\./g}/,,g' \
	-e 's,${UNIT_TESTS:C/\./\\\./g}/,,g' > ${.TARGET}.out || { \
	tail ${.TARGET}.out; mv ${.TARGET}.out ${.TARGET}.fail; exit 1; }
	diff -u ${UNIT_TESTS}/${.TARGET}.exp ${.TARGET}.out

accept:
	mv test.out ${.CURDIR}/test.exp


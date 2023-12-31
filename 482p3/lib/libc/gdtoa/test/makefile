# /****************************************************************
# Copyright (C) 1998, 2000 by Lucent Technologies
# All Rights Reserved
#
# Permission to use, copy, modify, and distribute this software and
# its documentation for any purpose and without fee is hereby
# granted, provided that the above copyright notice appear in all
# copies and that both that the copyright notice and this
# permission notice and warranty disclaimer appear in supporting
# documentation, and that the name of Lucent or any of its entities
# not be used in advertising or publicity pertaining to
# distribution of the software without specific, written prior
# permission.
#
# LUCENT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
# IN NO EVENT SHALL LUCENT OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
# SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
# THIS SOFTWARE.
#
# ****************************************************************/

CC = cc
CFLAGS = -g -I..
CFLAGS+=-I${.CURDIR}/../../arch/${MACHINE_ARCH}/gdtoa
L = -lm
L1 = -lm
#use "L1=-lm" when compiled with -DHonor_FLTP_ROUNDS or -DUSE_LOCALE
INFFIX = | sed 's/[Ii][Nn][Ff][intyINTY]*/Infinity/g'

.PATH: /usr/src/lib/libc/gdtoa

all: dt dItest ddtest dtest ftest Qtest xLtest xtest ddtestsi dItestsi tests

dt = dt.o $A
dt: $(dt)
	$(CC) -o dt $(dt) $L

dItest = dItest.o getround.o g_dfmt.o strtoId.o strtodI.o \
	g__fmt.o strtoIg.o
dItest: $(dItest)
	$(CC) -o dItest $(dItest) $(L1)

ddtest = ddtest.o getround.o g_dfmt.o strtordd.o strtopdd.o g_ddfmt.o \
	strtoIdd.o g__fmt.o strtoIg.o
ddtest: $(ddtest)
	$(CC) -o ddtest $(ddtest) $L

dtest = dtest.o getround.o g_dfmt.o strtopd.o strtoId.o \
	g__fmt.o strtoIg.o
dtest: $(dtest)
	$(CC) -o dtest $(dtest) $L

ftest = ftest.o getround.o strtorf.o strtopf.o g_ffmt.o strtoIf.o \
	g__fmt.o strtoIg.o
ftest: $(ftest)
	$(CC) -o ftest $(ftest) $(L1)

Qtest = Qtest.o getround.o strtorQ.o g_Qfmt.o strtoIQ.o strtopQ.o \
	g__fmt.o strtoIg.o
Qtest: $(Qtest)
	$(CC) -o Qtest $(Qtest) $(L1)

xtest = xtest.o getround.o strtorx.o g_xfmt.o strtoIx.o \
	g__fmt.o strtoIg.o
xtest: $(xtest)
	$(CC) -o xtest $(xtest) $(L1)

xLtest = xLtest.o getround.o strtorxL.o strtopxL.o g_xLfmt.o strtoIxL.o \
	g__fmt.o strtoIg.o
xLtest: $(xLtest)
	$(CC) -o xLtest $(xLtest) $(L1)

ddtestsi = ddtest.o strtopddSI.o strtorddSI.o strtoIddSI.o getround.o \
	g_dfmt.o g_ddfmt.o g__fmt.o strtoIg.o
ddtestsi: $(ddtestsi)
	$(CC) -o ddtestsi $(ddtestsi) $L

dItestsi = dItest.o strtodISI.o strtoIdSI.o getround.o \
	g_dfmt.o g__fmt.o strtoIg.o
dItestsi: $(dItestsi)
	$(CC) -o dItestsi $(dItestsi) $(L1)

strtodt = strtodt.o $A
strtodt: $(strtodt)
	$(CC) -o strtodt $(strtodt) $L

pftest = pftest.o $A
pftest: $(pftest)
	$(CC) -o pftest $(pftest) $L

## On Intel (and Intel-like) systems using extended-precision registers
## for double-precision (C type double) computations that sometimes suffer
## double rounding errors, the test below involving strtodt generally shows
## five lines of unexpected results.  Variant strtodtnrp uses ../strtodrnp.c
## (which does all computations in integer arithmetic) and should show no
## unexpected results.

strtodtnrp = strtodt.o strtodnrp.o
strtodtnrp: $(strtodtnrp)
	$(CC) -o strtodtnrp $(strtodtnrp)

# xQtest generates cp commands that depend on sizeof(long double).
# See the source for details.  If you know better, create Q.out,
# x.out and xL.out by copying the relevant *.ou0 or *.ou1 files
# to the corresponding .out files.  In short, the *.ou0 files are
# for long double == double; x.ou1 and xL.ou1 are for
# long double == extended (a la 80x87 and MC680x0), and Q.ou1 is
# for long double == quad.

Q.out x.out xL.out:
	$(CC) -o xQtest xQtest.c
	./xQtest | sh
	rm -f xQtest xQtest.o

## The rmdir below will fail if any test results differ.

tests: Q.out x.out xL.out dt dItest ddtest dtest ftest Qtest xLtest xtest ddtestsi dItestsi strtodt strtodtnrp
	mkdir bad
	cat testnos testnos1 | ./dt $(INFFIX) >zap 2>&1
	cmp dtst.out zap || mv zap bad/dtst.out
	./dItest <testnos $(INFFIX) >zap 2>&1
	cmp dI.out zap || mv zap bad/dI.out
	./dItestsi <testnos $(INFFIX) >zap 2>&1
	cmp dIsi.out zap || mv zap bad/dIsi.out
	./ddtestsi <testnos $(INFFIX) >zap 2>&1
	cmp ddsi.out zap || mv zap bad/ddsi.out
	for i in dd d f x xL Q; do cat testnos rtestnos | \
	 ./"$$i"test $(INFFIX) >zap 2>&1;\
	cmp $$i.out zap || mv zap bad/$$i.out; done
	./strtodt testnos3 >bad/strtodt.out && rm bad/strtodt.out || \
		cat bad/strtodt.out
	./strtodtnrp testnos3 >bad/strtodtnrp.out && rm bad/strtodtnrp.out || \
		cat bad/strtodtnrp.out
	rmdir bad 2>/dev/null || \
	(cd bad; for i in *; do cmp -s $$i ../obad/$$i && rm $$i;done; cd ..; rmdir bad)
	touch tests

# To test Printf in ../gdtoa.a, "make pf_test" and perhaps "make pf_testLq"
# (if both long double and quad are desired and available).

pf_test: pftest
	./pftest <pftestnos >zap
	cmp pftest.out zap && rm zap

pf_testLq: pftest
	./pftest <pfLqtestnos >zap
	cmp pftestLq.out zap && rm zap

xs0 = README Q.ou0 Q.ou1 Qtest.c d.out dI.out dIsi.out dItest.c dd.out\
	 ddsi.out ddtest.c dt.c dtest.c dtst.out f.out ftest.c\
	 getround.c makefile pfLqtestnos pftest.c pftestQ.out\
	 pftestx.out pftestLq.out pftestnos rtestnos strtoIdSI.c\
	 strtoIddSI.c strtodISI.c strtodt.c strtopddSI.c strtorddSI.c\
	 testnos testnos1 testnos3 x.ou0 x.ou1 xL.ou0 xL.ou1 xLtest.c\
	 xQtest.c xtest.c

# invoke "make -r xsum.out"
xsum.out: xsum0.out $(xs0)
	xsum $(xs0) >xsum1.out
	cmp xsum0.out xsum1.out && mv xsum1.out xsum.out || diff xsum[01].out

clean:
	rm -f *.[ao] dt *test *testsi pftest.out strtodt strtodtnrp xsum.out\
	 xsum1.out tests zap x.out xL.out Q.out
	rm -rf bad

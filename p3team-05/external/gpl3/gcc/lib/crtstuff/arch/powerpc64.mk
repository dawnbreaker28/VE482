# This file is automatically generated.  DO NOT EDIT!
# Generated from: 	NetBSD: mknative-gcc,v 1.65 2011/10/13 19:52:33 matt Exp 
# Generated from: NetBSD: mknative.common,v 1.9 2007/02/05 18:26:01 apb Exp 
#
G_INCLUDES=-I. -I. -I${GNUHOSTDIST}/gcc -I${GNUHOSTDIST}/gcc/. -I${GNUHOSTDIST}/gcc/../include -I./../intl -I${GNUHOSTDIST}/gcc/../libcpp/include     -I${GNUHOSTDIST}/gcc/../libdecnumber -I${GNUHOSTDIST}/gcc/../libdecnumber/dpd -I../libdecnumber   -I/usr/include/libelf
G_CRTSTUFF_CFLAGS=-O2  -DIN_GCC   -W -Wall -Wwrite-strings -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition  -isystem ./include  -I. -I. -I${GNUHOSTDIST}/gcc -I${GNUHOSTDIST}/gcc/. -I${GNUHOSTDIST}/gcc/../include -I./../intl -I${GNUHOSTDIST}/gcc/../libcpp/include     -I${GNUHOSTDIST}/gcc/../libdecnumber -I${GNUHOSTDIST}/gcc/../libdecnumber/dpd -I../libdecnumber   -I/usr/include/libelf  -g0 -finhibit-size-directive -fno-inline -fno-exceptions -fno-zero-initialized-in-bss -fno-toplevel-reorder -fno-tree-vectorize 
G_CRTSTUFF_T_CFLAGS=
G_tm_defines=NETBSD_ENABLE_PTHREADS
G_xm_file=
G_xm_defines=

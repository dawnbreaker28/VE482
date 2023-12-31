#!/bin/sh -
#
# Copyright (c) 1991, 1993
#	The Regents of the University of California.  All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# Kenneth Almquist.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 4. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#	@(#)mkbuiltins	8.2 (Berkeley) 5/4/95
# $FreeBSD: src/bin/sh/mkbuiltins,v 1.13 2004/04/06 20:06:51 markm Exp $

#temp=`/usr/bin/mktemp -t ka`
temp=/tmp/mkb$$
havehist=1
if [ "X$1" = "X-h" ]; then
	havehist=0
	shift
fi
havejobs=0
if [ "X$1" = "X-j" ]; then
	havejobs=0
	shift
elif grep '^#define[	 ]*JOBS[	 ]*1' $2 > /dev/null
then	havejobs=1
fi
objdir=$1
exec > ${objdir}/builtins.c
cat <<\!
/*
 * This file was generated by the mkbuiltins program.
 */

#include <stdlib.h>
#include "shell.h"
#include "builtins.h"

!
awk '/^[^#]/ {if(('$havejobs' || $2 != "-j") && ('$havehist' || $2 != "-h")) \
    print $0}' $3 | sed 's/-[hj]//' > $temp
#awk '{	printf "int %s();\n", $1}' $temp
echo '
int (*const builtinfunc[]) (int, char **) = {'
awk '/^[^#]/ {	printf "\t%s,\n", $1}' $temp
echo '};

const struct builtincmd builtincmd[] = {'
awk '{	for (i = 2 ; i <= NF ; i++) {
		printf "\t{ \"%s\", %d },\n",  $i, NR-1
	}}' $temp
echo '	{ NULL, 0 }
};'

exec > ${objdir}/builtins.h
cat <<\!
/*
 * This file was generated by the mkbuiltins program.
 */

!
tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ < $temp |
	awk '{	printf "#define %s %d\n", $1, NR-1}'
echo '
struct builtincmd {
      char *name;
      int code;
};

extern int (*const builtinfunc[]) (int, char **);
extern const struct builtincmd builtincmd[];'
awk '{ printf "int %s (int, char **);\n", $1 }' < $temp
rm -f $temp

#
# $PchId: mkbuiltins,v 1.6 2006/05/22 12:42:58 philip Exp $

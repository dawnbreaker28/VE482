/*	$NetBSD: scanner.l,v 1.1.1.1 2009/10/26 00:29:11 christos Exp $	*/

/*
 * This file is part of flex.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the University nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.
 */

%{
/* This test is for correctness of extended (?...) patterns. */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

%}

%option 8bit outfile="scanner.c" prefix="test"
%option nounput nomain noyywrap
%option warn


%%

    /* Output should match the input. */

abc(?# Single Line Comment )def    ECHO;
ghi(?#
    multi-line
    comment
    )jkl                           ECHO;

mno(?#
    multi-line //
    comment with ##
    ~~!@#$ %^&*(@-_+=\|,.<>/ ?: ;
    punctuation
    )pqr                           ECHO;
(?# Start of a rule.)stu           ECHO;
vwxyz(?#End of a rule.)            ECHO;
A(?x: B
    /* comment */
    C D)                           ECHO;

\n                                 ECHO;
%%

int main(void);

int
main ()
{
    yyin = stdin;
    yyout = stdout;
    yylex();
    //printf("TEST RETURNING OK.\n");
    return 0;
}

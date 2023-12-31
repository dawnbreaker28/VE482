/*	$NetBSD: scanner.l,v 1.1.1.1 2009/10/26 00:29:31 christos Exp $	*/

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
/* A template scanner file to build "scanner.c". 
   The scanner is not really important -- we only care if
   it compiles under a c++ compiler, and runs. */
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
/*#include "parser.h" */

%}

%option 8bit outfile="scanner.cpp" prefix="test"
%option nounput nomain noyywrap 
%option warn reentrant


%%

.              { }

%%

int main(void);

int
main ()
{
    yyscan_t  lexer;
    yylex_init( &lexer );
    yyset_out ( stdout,lexer);
    yyset_in  ( stdin, lexer);
    while( yylex(lexer) )
    {
    }
    yylex_destroy( lexer );
    printf("TEST RETURNING OK.\n");
    return 0;
}

/*	$NetBSD: scanner.l,v 1.1.1.1 2009/10/26 00:29:30 christos Exp $	*/

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
/* A template scanner file to build "scanner.c". */
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
/*#include "parser.h" */

%}

%option 8bit outfile="scanner.c" prefix="test"
%option nounput nomain noyywrap 
%option warn array reentrant


%%

.|\n    { }


%%

int main(void);

int
main ()
{
    yyscan_t lexer;
    
	yylex_init(&lexer);
    yyset_in(stdin, lexer);
    yyset_out(stdout, lexer);
	
    yylex( lexer );
	
    yylex_destroy( lexer);
    printf("TEST RETURNING OK.\n");

    return 0;
}

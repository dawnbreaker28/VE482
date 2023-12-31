/*	$NetBSD: scanner.l,v 1.1.1.1 2009/10/26 00:29:12 christos Exp $	*/

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
%}

%option 8bit outfile="scanner.c" prefix="test"
%option nounput nomain noyywrap reentrant
%option warn stack never-interactive
%x STATE_1

%%

<INITIAL>{
0              yy_push_state (STATE_1, yyscanner);
.|\n           return 1;
}
<STATE_1>{
1              yy_pop_state(yyscanner);
.|\n           return yy_top_state(yyscanner) + 1;
}

%%

int
main (int argc, char* const argv[])
{
    FILE* fp;
    int i;
    yyscan_t  yyscanner;

    if ((fp = fopen(argv[1],"r")) == NULL){
        perror("Failed to open input file.");
        return 1;
    }

    printf("Test 1: Reusing same scanner.\n");
    yylex_init( &yyscanner );
    yyset_out ( stdout, yyscanner);

    for (i=0; i <  4; ++i){

        rewind(fp);
        yyset_in  ( fp, yyscanner);

        while( yylex(yyscanner) )
            ;
    }
    yylex_destroy( yyscanner );
    printf("Test 1 OK\n\n");

    printf("Test 2: Rescanning with new scanner each time.\n");

    memset(&yyscanner,0,sizeof(yyscanner)); // Just to be clean about it.

    for (i=0; i < 4; ++i){
        yyscan_t  s;
        yylex_init( &s );
        yyset_out ( stdout, s);
        rewind(fp);
        yyset_in  ( fp, s);

        while( yylex(s) )
            ;
        yylex_destroy( s );
    }
    printf("Test 2 OK\n\n");


    printf("TEST RETURNING OK.\n");
    return 0;
}

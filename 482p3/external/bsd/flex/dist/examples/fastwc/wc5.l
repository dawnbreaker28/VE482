/*	$NetBSD: wc5.l,v 1.1.1.1 2009/10/26 00:28:34 christos Exp $	*/

/* Oops; slight change from wc3.l introduces backtracking */

ws    [ \t]
nonws [^ \t\n]
word  {ws}*{nonws}+
words {word}{ws}+

%option main noyywrap
%%
	int cc = 0, wc = 0, lc = 0;

{word}{ws}*		cc += yyleng; ++wc;
{word}{ws}*\n		cc += yyleng; ++wc; ++lc;
{words}{word}		cc += yyleng; wc += 2;	/* oops */
{words}{2}{word}{ws}*	cc += yyleng; wc += 3;
{words}{3}{word}{ws}*	cc += yyleng; wc += 4;

{ws}+			cc += yyleng;

\n+			cc += yyleng; lc += yyleng;

<<EOF>>		{
		printf( "%8d %8d %8d\n", lc, wc, cc );
		yyterminate();
		}

/*	$NetBSD: wc3.l,v 1.1.1.1 2009/10/26 00:28:34 christos Exp $	*/

/* Somewhat faster still: potentially match a lot of text with each rule */

ws    [ \t]
nonws [^ \t\n]
word  {ws}*{nonws}+
words {word}{ws}+

%option main noyywrap
%%
	int cc = 0, wc = 0, lc = 0;

{word}{ws}*		cc += yyleng; ++wc;
{word}{ws}*\n		cc += yyleng; ++wc; ++lc;
{words}{word}{ws}*	cc += yyleng; wc += 2;
{words}{2}{word}{ws}*	cc += yyleng; wc += 3;
{words}{3}{word}{ws}*	cc += yyleng; wc += 4;

{ws}+			cc += yyleng;

\n+			cc += yyleng; lc += yyleng;

<<EOF>>		{
		printf( "%8d %8d %8d\n", lc, wc, cc );
		yyterminate();
		}

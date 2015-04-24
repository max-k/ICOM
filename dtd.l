/*
CNUM (\+|\-)?[0-9]{1,10}
(\+|\-)?[0-9]{1,10} { yylval.num = atoi(yytext); return CNUM; }
(\+|\-)?[0-9]{1,10}:(\+|\-)?[0-9]{1,10} { return CNUM; }
\#.*\n  ;
[ \t\r\n] ;
. {return ERROR;}
STR { return STR; }
INT { return INT; }
.           { printf("ERROR\n"); return ERROR; }

*/
%option noyywrap

%{
#include <stdio.h>
#include "dtd.tab.h"
int cnt = 1;
int rdt = 0;
%}

%x RDT

COMMENT \#.*$
SPACE [ \t\r]
NOSPACE [^ \t\r]
PUNCT [,:=\(\)\{\}]
QSTRING [^\"]+
OPERATOR [&|]
SUFFIX [?+*]
IDENT [a-zA-Z][a-zA-Z0-9]*

%%

<INITIAL>RAWDATA    { printf("RAWDATA\n"); BEGIN RDT; return RAWDATA; }
<RDT>=              { printf("rawdata =\n"); return *yytext; }
<RDT>\"             { rdt++; printf("rawdata \" (%i)\n", rdt);
                        if (rdt % 2 == 0) BEGIN INITIAL; }
<RDT>{QSTRING}      { printf("STRING : %s\n", yytext); return STRING; }
<INITIAL>EMPTY      { printf("EMPTY\n"); return EMPTY; }
<INITIAL>DATA       { printf("DATA\n"); return DATA; }
<INITIAL>\n         { cnt++; printf("LF (beginning line %i)\n", cnt); }
<INITIAL>STRING     { printf("STR\n"); return STR; }
<INITIAL>CNUM       { printf("CNUM\n"); return CNUM; }
<INITIAL>INT        { printf("INT\n"); return INT; }
<INITIAL>{COMMENT}  { printf("COMMENT\n"); }
<INITIAL>{SPACE}    { printf("SPACE\n"); }
<INITIAL>{OPERATOR} { printf("OPERATOR : %s\n", yytext); return *yytext; }
<INITIAL>{SUFFIX}   { printf("SUFFIX : %s\n", yytext); return *yytext; }
<INITIAL>{PUNCT}    { printf("PUNCT : %s\n", yytext); return *yytext; }
<INITIAL>{IDENT}    { printf("IDENT : %s\n", yytext); return IDENT; }

%%

void yyerror(const char *mess)
{
    fprintf(stderr, "line %i : %s (near %s)\n", cnt, mess, yytext);
    exit(1);
}


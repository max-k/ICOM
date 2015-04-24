%option noyywrap

%{
#include <stdio.h>
#include "xml.tab.h"
int cnt = 1;
%}

%option stack

%s ATTS
%x LINT
%x LSTR
%s LDATA
%s LRAW

ID      [a-zA-Z0-9]
SPACE   [ \t\r]
NOSPACE [ \t\r\n]

%%

<ATTS>{ID}          { printf("ID : %s\n", yytext); return *yytext; }
<ATTS>=             { printf("EQUAL\n"); return *yytext; }
<ATTS>,             { printf("COMMA\n"); return *yytext; }
<LINT>[0-9]+        { printf("INT\n"); yylval=atoi(yytext); return INT; }
<LSTR>\"            { printf("QUOTE\n"); return *yytext; }
<LSTR>[^\"]+        { printf("STR : %s\n", yytext); yylval=*yytext; return STR; }
<LDATA>[^</]+       { printf("DATA : %s\n", yytext); yylval=*yytext; return DATA; }
<LRAW>[^</]+"-:)"   { printf("RAW : %s\n", yytext); yylval=*yytext; return DATA; }
<INITIAL>"<b0"      { printf("START B0\n"); return B0; }
<INITIAL>"<b1"      { printf("START B1\n"); return B1; }
<INITIAL>"<b2"      { printf("START B2\n"); return B2; }
<INITIAL>"<b3"      { printf("START B3\n"); return B3; }
<INITIAL>"<b4"      { printf("START B4\n"); return B4; }
<INITIAL>>          { printf("CLOSURE\n"); return *yytext; }
<INITIAL>"/>"       { printf("SHORTEND\n"); return SHORTEND; }
<INITIAL>"</b0>"    { printf("END B0\n"); return EB0; }
<INITIAL>"</b1>"    { printf("END B1\n"); return EB1; }
<INITIAL>"</b2>"    { printf("END B2\n"); return EB2; }
<INITIAL>"</b3>"    { printf("END B3\n"); return EB3; }
<INITIAL>"</b4>"    { printf("END B4\n"); return EB4; }
<*>{SPACE}          { printf("SPACE\n"); }
<*>\n               { cnt++; printf("LF(beginning line %i)\n", cnt); }

%%

void yyerror(const char *mess)
{
    fprintf(stderr,
            "line %i : %s (near %s) [state: %i]\n",
            cnt, mess, yytext, yy_top_state());
    exit(1);
}
void pop_state()
{
    printf("-> end state %i (current %i)\n", YY_START, yy_top_state());
    yy_pop_state();
}
void push_atts_state()
{
    printf("-> state %i : ATTS\n", ATTS);
    yy_push_state(ATTS);
}
void push_int_state()
{
    printf("-> state %i : LINT\n", LINT);
    yy_push_state(LINT);
}
void push_str_state()
{
    printf("-> state %i : LSTR\n", LSTR);
    yy_push_state(LSTR);
}
void push_data_state()
{
    printf("-> state %i : LDATA\n", LDATA);
    yy_push_state(LDATA);
}
void push_rdata_state()
{
    printf("-> state %i : LRAW\n", LRAW);
    yy_push_state(LRAW);
}

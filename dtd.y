%{
#include "dtd.h"
%}

%token      IDENT
%token      CNUM
%token      STRING
%token      STR
%token      INT
%token      DATA
%token      RAWDATA
%token      EMPTY

%left '|'
%left '&'
%precedence expr
%precedence op

%%

dtd: balise ;
balise: '{' IDENT attributs content '}' ;
attributs: attributs ',' attribut
    | attribut
    |
;
attribut: IDENT '=' STR
    | IDENT '=' INT
    | IDENT '=' CNUM
    | IDENT '=' CNUM ':' CNUM
    | IDENT '=' '(' identifiants ')'
;
identifiants: identifiants IDENT
    | IDENT
;
content: EMPTY
    | RAWDATA '=' STRING
    | DATA
    | '(' expression ')' suffix
    | INT
    |
;
expression
    : '(' expression ')' suffix
    | expression operateur expression %prec expr
    | balise suffix
    | IDENT suffix
;
operateur
    : '&' %prec op
    | '|' %prec op
;
suffix: ':' CNUM
    | '?'
    | '*'
    | '+'
    |
;


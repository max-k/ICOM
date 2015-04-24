/* Déclaration des fonctions de base de lex */
int yylex();
int yyparse();
void yyerror(const char *mess);
/* Déclaration des fonctions liées aux start conditions */
void pop_state();
void push_atts_state();
void push_int_state();
void push_str_state();
void push_data_state();
void push_rdata_state();

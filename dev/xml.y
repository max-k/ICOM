%{
#include "xml.h"
%}

%token  B0 EB0
%token  B1 EB1
%token  B2 EB2
%token  B3 EB3
%token  B4 EB4
%token  INT
%token  STR
%token  DATA
%token  SHORTEND

%%

xml: b0 ;
b0: B0 b0_atts '>' b0_tree EB0 ;
b0_atts: { push_atts_state(); } b0_att0 b0_att1 { pop_state(); } ;
b0_att0: 'N' '=' { push_int_state(); } INT { pop_state(); } ;
b0_att1: 'S' 'S' '=' { push_str_state(); } '"' STR '"' { pop_state(); } ;
b0_tree: b0_child0 b0_child1 ;
b0_child0: b0_child0_child0 | b0_child0_child1 ;
b0_child1: b0_child1 b0_child1_child0 | b0_child1 b0_child1_child1 | ;
b0_child0_child0: b1 | b0_child0_child0 b1 ;
b0_child0_child1: b2 | b0_child0_child1 b2 ;
b0_child1_child0: b3 | b0_child1_child0 b3 ;
b0_child1_child1: b4 ;
b1: B1 '>' { push_data_state(); } DATA { pop_state(); } EB1 | B1 SHORTEND ;
b2: B2 '>' { push_rdata_state(); } DATA { pop_state(); } EB2 ;
b3: B3 '>' { push_int_state(); } INT { pop_state(); } EB3 ;
b4: B4 '>' b4_tree EB4 ;
b4_tree: b1 b2 ;


%token <y_word> GPR
%token <y_word> FPR
%token <y_word> FMT
%token <y_word> FMT3
%token <y_word> FCOND

%type <y_word> gpr fpr
%type <y_word> e16 e9
%type <y_word> u25 u20 u16 u5 u3
%type <y_word> abs26 offset16

%type <y_word> extmsblsb insmsblsb

#include "definitions.y"


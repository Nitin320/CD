%{  
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  void yyerror(const char *s);  
%}

%token Number Identifier
%left '+' '-'
%left '*' '/'

%%
Arithmetic:
    expr{printf("Valid Expression"); exit(0);}
expr:
    Number
    | Identifier
    | expr'+'expr
    | expr'-'expr
    | expr'*'expr
    | expr'/'expr
    ;
%%

void yyerror(const char *s){
    printf("Invalid");
}

int main(){
    printf("Enter expression : ");
    yyparse();
    return 0;
}

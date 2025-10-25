%{  
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  void yyerror(const char *s);  
%}

%token Number Identifier Invalid
%left '+'

%%
Arithmetic:
    No {printf("INVALIDDD"); exit(0);}
    expr {printf("Valid"); exit(0);}
expr:
    expr '+' expr
    | Number
    | Identifier
No:
    Invalid
%%

void yyerror(const char *s){
    printf("Invalid");
}

int main(){
    printf("Enter expression : ");
    yyparse();
    return 0;
}

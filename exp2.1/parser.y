%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(const char* s);    
%}

%token Number
%left '+' '-'
%left '*' '/'

%%
answer:
    expr {printf("%d", $$);exit(0);}
expr:
    Number
    | expr'+'expr {$$=$1+$3;}
    | expr'-'expr {$$=$1-$3;}
    | expr'*'expr {$$=$1*$3;}
    | expr'/'expr {$$=$1/$3;}
%%

void yyerror(const char* s){
    exit(1);
}

int main(){
    printf("Enter stuff : ");
    yyparse();
    return 0;
}
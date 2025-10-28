%{
    #include <stdio.h>
    #include "parser.tab.h" 
%}

%%
[0-9] {return Number;}
[a-z|A-Z][a-z|A-Z|0-9]* {return Identifier;}
\n {return 0;}
[+|-|*|/] {return yytext[0];}
. {printf("Invalid"); exit(1);}
%%

int yywrap(void){
    return 1;
}
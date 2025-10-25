%{
    #include <stdio.h>
    #include "parser.tab.h" 
%}

%%
[0-9] {return Number;}
[a-z|A-Z][a-z|A-Z|0-9]* {return Identifier;}
[-] {return Inavlid;}
%%

int yywrap(void){
    return 1;
}
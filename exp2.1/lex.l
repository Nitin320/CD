%{
    #include <stdio.h>    
    #include "parser.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return Number;}
[+] {return '+';}
[-] {return '-';}
[*] {return '*';}
[/] {return '/';}
[\n] {return 0;}
. {return yytext[0];}
%%


int yywrap(void){
    return 1;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[10];
int error = 0, i = 0;

void E(){
    T();
    Eprime();
}
void Eprime(){
    if(input[i] == '+'){
        i++;
        E();
    }
}
void T(){
    F();
    Tprime();
}
void Tprime(){
    if(input[i] == '*'){
        i++;
        T();
    }
}
void F(){
    if(isalnum(input[i])) i++;
    else if(input[i] == '('){
        i++;
        E();
        if(input[i]  == ')') i++;
        else error = 1;
    }
    else error = 1;
}

int main(){
    printf("Enter in the expression : ");
    scanf("%s", input);
    E();
    if(strlen(input) == i && error == 0) printf("Accepted");
    else printf("Rejected");
}

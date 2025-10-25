#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){

    char exp[20], op[20], arg1[20], arg2[20];
    char operators[]  = "/*+-";
    int count = 0;

    printf("Enter the expression");
    scanf("%s", exp);

    for(int i=0; i<4; i++){
        for(int j=0; j<exp[j]; j++){
            if(exp[j] == operators[i]){
                op[count] = exp[j];
                arg1[count] = exp[j-1];
                arg2[count] = exp[j+1];
                exp[j-1] = count + '0';
                strcpy(&exp[j], &exp[j+2]);
                count++;
                j -= 1;
            }
        }
    }

    for(int i=0; i<count; i++){
        printf("t%d = ", i+1);
        isdigit(arg1[i]) ? printf("t%d", arg1[i] - '0'+1) : printf("%c", arg1[i]);
        printf("%c", op[i]);
        isdigit(arg2[i]) ? printf("t%d", arg2[i] - '0'+1) : printf("%c\n", arg2[i]);
    }

}
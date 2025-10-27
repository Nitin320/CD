#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct cod{
    char lhs[10], o1[10], o2[10];
    char op;
} c[10];

int main(){

    int n;
    char reg[10];
    printf("Enter the number of statements : ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        int r = scanf("%s = %s %c %s", c[i].lhs, c[i].o1, &c[i].op, c[i].o2);
        if(r == 3){
            c[i].op = '=';
            strcpy(c[i].o2, "_");
        }
    }

    printf("Assermbly Code : \n");
    for(int i=0; i<n; i++){
        sprintf(reg, "R%d", i);

        if(c[i].op == '=') printf("MOV %s, %s\n", reg, c[i].o1);
        else{
            printf("MOV %s, %s\n", reg, c[i].o1);
            switch (c[i].op) {
                case '+': printf("ADD %s, %s\n", reg, c[i].o2); break;
                case '-': printf("SUB %s, %s\n", reg, c[i].o2); break;
                case '*': printf("MUL %s, %s\n", reg, c[i].o2); break;
                case '/': printf("DIV %s, %s\n", reg, c[i].o2); break;
                default:  printf("INVALID op\n");
            }
        }
        printf("MOV %s, %s\n", c[i].lhs, reg);

    }

}
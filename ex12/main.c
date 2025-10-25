#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

struct cod {
    char lhs[MAX], op1[MAX], op2[MAX];
    char op;
} c[MAX];

int main() {
    int n, i;
    char reg[MAX];

    printf("Enter the number of statements: ");
    scanf("%d", &n);
    printf("Enter the number of statements in TAC format (e.g., x = a * b):\n");

    for (i = 0; i < n; i++) {
        printf("\nStatement %d: ", i + 1);
    
        int scan_result = scanf("%s = %s %c %s", c[i].lhs, c[i].op1, &c[i].op, c[i].op2);

        if (scan_result == 3) {
            c[i].op = '='; 
            strcpy(c[i].op2, "_"); 
        }
    }

    printf("\nAssembly code:\n");
    for (i = 0; i < n; i++) {
        sprintf(reg, "R%d", i);

        if (c[i].op == '=') {
            printf("MOV %s, %s\n", reg, c[i].op1);
        } else {
            printf("MOV %s, %s\n", reg, c[i].op1);
            switch (c[i].op) {
                case '+': printf("ADD %s, %s\n", reg, c[i].op2); break;
                case '-': printf("SUB %s, %s\n", reg, c[i].op2); break;
                case '*': printf("MUL %s, %s\n", reg, c[i].op2); break;
                case '/': printf("DIV %s, %s\n", reg, c[i].op2); break;
                default:  printf("INVALID op\n");
            }
        }
        printf("MOV %s, %s\n", c[i].lhs, reg);
    }
    return 0;
}
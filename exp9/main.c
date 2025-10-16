#include <stdio.h>
#include <string.h>

int main() {
    char expr[50], op;
    int i, j, temp_count = 1;
    char operators[] = "/*+-";

    printf("Enter the expression: ");
    scanf("%s", expr);
    printf("\n--- Three-Address Code ---\n");

    for (j = 0; j < strlen(operators); j++) {
        op = operators[j];
        for (i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == op) {
                printf("t%d = %c %c %c\n", temp_count, expr[i - 1], op, expr[i + 1]);
                expr[i - 1] = temp_count + '0';
                
                for (int k = i; expr[k] != '\0'; k++) {
                    expr[k] = expr[k + 2];
                }
                temp_count++;
                i = -1;
            }
        }
    }
    
    printf("result = t%d\n", temp_count-1);
    return 0;
}
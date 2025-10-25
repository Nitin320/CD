#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char expr[20], ops[10], arg1s[10], arg2s[10];
    char operators[] = "/*+-";
    int i, j, count = 0;

    printf("Enter expression: ");
    scanf("%s", expr);

    for (j = 0; j < 4; j++) {
        for (i = 0; expr[i]; i++) {
            if (expr[i] == operators[j]) {
                ops[count] = expr[i];
                arg1s[count] = expr[i - 1];
                arg2s[count] = expr[i + 1];
                expr[i - 1] = count + '0'; 
                strcpy(&expr[i], &expr[i + 2]); 
                count++;
                i = -1; 
            }
        }
    }

    printf("\n--- Three-Address Code ---\n");
    for (i = 0; i < count; i++) {
        printf("t%d = ", i + 1);
        isdigit(arg1s[i]) ? printf("t%d ", arg1s[i] - '0' + 1) : printf("%c ", arg1s[i]); 
        printf("%c ", ops[i]);
        isdigit(arg2s[i]) ? printf("t%d\n", arg2s[i] - '0' + 1) : printf("%c\n", arg2s[i]); 
    }
}
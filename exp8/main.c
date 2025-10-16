#include <stdio.h>
#include <string.h>

int get_terminal_index(char c, char* terminals, int n) {
    for (int i = 0; i < n; i++) {
        if (terminals[i] == c) return i;
    }
    return -1;
}

int main() {
    char terminals[10], table[10][10], input[50], stack[50];
    int n, i, j, stack_top = 0, input_ptr = 0;

    printf("Enter terminals: ");
    scanf("%s", terminals);
    n = strlen(terminals);

    printf("Enter precedence table (%dx%d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf(" %c", &table[i][j]);
        }
    }

    printf("Enter input string: ");
    scanf("%s", input);

    stack[0] = '$';
    stack[1] = '\0';
    printf("\nSTACK\t\tSTRING\t\tACTION\n-----\t\t------\t\t------\n");

    while (1) {
        char stack_char = stack[stack_top];
        char input_char = input[input_ptr];
        int stack_idx = get_terminal_index(stack_char, terminals, n);
        int input_idx = get_terminal_index(input_char, terminals, n);

        if (stack_char == '$' && input_char == '$') {
            printf("%-15s %-15s ACCEPTED!\n", stack, input + input_ptr);
            break;
        }

        char relation = table[stack_idx][input_idx];
        if (relation == '<' || relation == '=') {
            printf("%-15s %-15s Shift %c\n", stack, input + input_ptr, input_char);
            stack[++stack_top] = input_char;
            stack[stack_top + 1] = '\0';
            input_ptr++;
        } else if (relation == '>') {
            printf("%-15s %-15s Reduced\n", stack, input + input_ptr);
            stack[stack_top--] = '\0';
        } else {
            printf("ERROR\n");
            break;
        }
    }
    return 0;
}
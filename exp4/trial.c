#include <stdio.h>

#define MAX_STATES 10

int main() {
    int num_states, num_trans, adj[MAX_STATES][MAX_STATES] = {0};

    printf("Enter in the number of states: ");
    scanf("%d", &num_states);
    printf("Enter in the number of transitions: ");
    scanf("%d", &num_trans);

    printf("Enter transitions (e.g., 0 e 1):\n");
    for (int i = 0; i < num_trans; i++) {
        int from, to;
        char symbol;
        scanf("%d %c %d", &from, &symbol, &to);
        if (symbol == 'e') {
            adj[from][to] = 1;
        }
    }

    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < num_states; i++) {
        int stack[MAX_STATES], top = -1, closure[MAX_STATES] = {0};

        stack[++top] = i;
        closure[i] = 1;

        while (top != -1) {
            int u = stack[top--];
            for (int v = 0; v < num_states; v++) {
                if (adj[u][v] && !closure[v]) {
                    closure[v] = 1;
                    stack[++top] = v;
                }
            }
        }

        printf("q%d = { ", i);

        for (int j = 0; j < num_states; j++) {
            if (closure[j]) {
                printf("q%d,", j);
            }
        }
        printf(" }\n");
    }

    return 0;
}
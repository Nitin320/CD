#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define LEN 10

typedef struct {
    char op[2], o1[LEN], o2[LEN], r[LEN];
    int is_const, val;
} St;

St s[MAX]; int n;

int main() {
    printf("Statements: "); scanf("%d", &n);
    printf("Enter (res = op1 op op2) [use _ for op]:\n");
    for (int i = 0; i < n; i++) {
        char eq[2];
        scanf("%s %s %s %s %s", s[i].r, eq, s[i].o1, s[i].op, s[i].o2);
        if (s[i].op[0] == '_') s[i].op[0] = '=';
        s[i].is_const = 0;
    }

    printf("\nAfter propagation:\n");
    for (int i = 0; i < n; i++) {
        int v1, v2, res, c1 = 0, c2 = 0;

        if (isdigit(s[i].o1[0])) { v1 = atoi(s[i].o1); c1 = 1; }
        else for (int j = 0; j < i; j++)
            if (s[j].is_const && strcmp(s[j].r, s[i].o1) == 0) {
                v1 = s[j].val; c1 = 1; break;
            }
        
        if (isdigit(s[i].o2[0])) { v2 = atoi(s[i].o2); c2 = 1; }
        else for (int j = 0; j < i; j++)
            if (s[j].is_const && strcmp(s[j].r, s[i].o2) == 0) {
                v2 = s[j].val; c2 = 1; break;
            }

        if (s[i].op[0] == '=' && c1) res = v1;
        else if (c1 && c2) {
            if (s[i].op[0] == '+') res = v1 + v2;
            else if (s[i].op[0] == '-') res = v1 - v2;
            else if (s[i].op[0] == '*') res = v1 * v2;
            else if (s[i].op[0] == '/' && v2 != 0) res = v1 / v2;
            else c1 = 0;
        } else c1 = 0;

        if (c1) {
            s[i].is_const = 1; s[i].val = res;
            printf("%s = %d _ _\n", s[i].r, res);
        } else {
            printf("%s = %s %s %s\n", s[i].r, s[i].o1, s[i].op, s[i].o2);
        }
    }
    return 0;
}
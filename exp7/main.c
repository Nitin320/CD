#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char p[20][20];
char fi[26][20];
char fo[26][20];
int nt[26] = {0};

int add(char* s, char c) {
    if (strchr(s, c) == NULL) {
        s[strlen(s)] = c;
        return 1;
    }
    return 0;
}

void first(char* r, char* s) {
    if (s[0] == '\0') {
        add(r, 'e');
        return;
    }
    if (!isupper(s[0])) {
        add(r, s[0]);
        return;
    }
    int idx = s[0] - 'A';
    char* f = fi[idx];
    int eps = 0;

    for (int i = 0; i < strlen(f); i++) {
        if (f[i] == 'e') eps = 1;
        else add(r, f[i]);
    }
    if (eps) {
        first(r, s + 1);
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (S=e for epsilon):\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", p[i]);
        nt[p[i][0] - 'A'] = 1;
    }

    int ch = 1;
    while (ch) {
        ch = 0;
        for (int i = 0; i < n; i++) {
            int h = p[i][0] - 'A';
            char* b = &p[i][2];
            char tmp[20] = "";
            first(tmp, b);
            for (int k = 0; k < strlen(tmp); k++) {
                if (add(fi[h], tmp[k])) {
                    ch = 1;
                }
            }
        }
    }

    add(fo[p[0][0] - 'A'], '$');
    ch = 1;
    while (ch) {
        ch = 0;
        for (int i = 0; i < n; i++) {
            int h = p[i][0] - 'A';
            char* b = &p[i][2];
            for (int j = 0; j < strlen(b); j++) {
                if (!isupper(b[j])) continue;
                int idx = b[j] - 'A';
                char* rst = &b[j + 1];
                char tmp[20] = "";
                first(tmp, rst);
                int eps = 0;
                for (int k = 0; k < strlen(tmp); k++) {
                    if (tmp[k] == 'e') eps = 1;
                    else if (add(fo[idx], tmp[k]))
                        ch = 1;
                }
                if (strlen(rst) == 0 || eps) {
                    for (int k = 0; k < strlen(fo[h]); k++)
                        if (add(fo[idx], fo[h][k]))
                            ch = 1;
                }
            }
        }
    }

    printf("\n--- FIRST Sets ---\n");
    for (int i = 0; i < 26; i++) {
        if (nt[i]) {
            printf("FIRST(%c) = { %s }\n", (char)(i + 'A'), fi[i]);
        }
    }
    printf("\n--- FOLLOW Sets ---\n");
    for (int i = 0; i < 26; i++) {
        if (nt[i]) {
            printf("FOLLOW(%c) = { %s }\n", (char)(i + 'A'), fo[i]);
        }
    }
    return 0;
}
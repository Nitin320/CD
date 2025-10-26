#include <stdio.h>
#include <string.h>

int n_s, n_t;
char s[27], t[50][4], cl[26][27], ab[20] = "";

// add char to set
int add(char* set, char c) {
    if (!strchr(set, c)) { set[strlen(set)] = c; return 1; }
    return 0;
}

// find closure (recursive)
void fc(char* c_set, char state) {
    add(c_set, state);
    for (int i = 0; i < n_t; i++) {
        if (t[i][0] == state && t[i][1] == 'e' && !strchr(c_set, t[i][2])) {
            fc(c_set, t[i][2]);
        }
    }
}

int main() {
    printf("Num of states:");
    scanf("%d", &n_s);
    printf("State names:");
    for (int i = 0; i < n_s; i++) scanf(" %c", &s[i]);
    
    printf("Num of transitions:");
    scanf("%d", &n_t);
    for (int i = 0; i < n_t; i++) {
        scanf(" %c %c %c", &t[i][0], &t[i][1], &t[i][2]);
        if (t[i][1] != 'e') add(ab, t[i][1]); // add to alphabet
    }

    printf("\nEpsilon closures\n");
    for (int i = 0; i < n_s; i++) {
        fc(cl[s[i] - 'a'], s[i]);
        printf("Closure(%c) = {%s}\n", s[i], cl[s[i] - 'a']);
    }

    printf("\nNFA transitions\n");
    for (int i = 0; i < n_s; i++) { // For each state q
        for (int j = 0; j < strlen(ab); j++) { // For each symbol a
            char res[27] = "";
            char* e_cl_q = cl[s[i] - 'a'];
            
            for (int k = 0; k < strlen(e_cl_q); k++) { // For p in E(q)
                for (int m = 0; m < n_t; m++) { // Find p --a--> r
                    if (t[m][0] == e_cl_q[k] && t[m][1] == ab[j]) {
                        // Add E(r) to result set
                        char* e_cl_r = cl[t[m][2] - 'a'];
                        for(int n=0; n < strlen(e_cl_r); n++) add(res, e_cl_r[n]);
                    }
                }
            }
            printf("%c-%c = {%s}\n", s[i], ab[j], res);
        }
    }
    return 0;
}
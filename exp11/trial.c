#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    char r[10], op[10], o1[10], o2[10];
    int is_const, val;
} new;

new s[10];
int n;

int main(){

    printf("Enter in the number of statements : ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        char eq[2];
        scanf("%S %s %s %s %s", s[i].r, eq, s[i].o1, s[i].op, s[i].o2);
        if(s[i].op[0] == '_') s[i].op[0] = '=';
        s[i].is_const = 0;
    }

    for(int i=0; i<n; i++){
        int v1, v2, res, c1 = 0, c2 = 0;
        
        if(isdigit(s[i].o1[0])){
            v1 = atoi(s[i].o1); c1 = 1;
        }
        else{
            for(int j=0; j<i; j++){
                if(s[j].is_const && strcmp(s[j].r, s[i].o1) == 0){
                    v1 = s[j].val; c1 = 1; break;
                }
            }
        }

        if(isdigit(s[i].o2[0])){
            v2 = atoi(s[i].o2); c2 = 1;
        }
        else{
            for(int j=0; j<i; j++){
                if(s[j].is_const && strcmp(s[j].r, s[i].o2) == 0){
                    v2 = s[j].val; c2 = 1; break;
                }
            }
        }

        if(s[i].op[0] == '=' & c1) res = v1;
        else if(c1 && c2){
            if(s[i].op[0] == '+') res = v1 + v2;
            else if(s[i].op[0] == '-') res = v1 - v2;
            else if(s[i].op[0] == '*') res = v1 * v2;
            else if(s[i].op[0] == '/') res = v1 / v2;
            else c1 = 0;
        }
        else c1 = 0;

        if(c1){
            s[i].is_const = 1; s[i].val = res;
            printf("%s = %d _ \n", s[i].r, res);
        }
        else{
            printf("%s = %s %s %s\n", s[i].r, s[i].o1, s[i].op, s[i].o2);
        }
    }

}
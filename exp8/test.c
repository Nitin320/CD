#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_ind(char c, char* terminals, int n){
    for(int i=0; i<n; i++){
        if(terminals[i] == c) return i;
    }
    return -1;
}

int main(){

    char terminals[10], table[100][100], stack[10], input[10];
    int stop=0, itop=0;

    printf("Enter the terminals : ");
    scanf("%s", terminals);
    int n = strlen(terminals);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %c", &table[i][j]);
        }
    }

    printf("Enter input : ");
    scanf("%s", input);
    stack[0] = '$';
    stack[1] = '\0';

    while(1){

        char stack_curr = stack[stop];
        char input_curr = input[itop];
        int stack_ind = get_ind(stack_curr, terminals, n);
        int input_ind = get_ind(input_curr, terminals, n);

        if(stack_curr == '$' && input_curr == '$'){
            printf("%s\t%s\t ACCEPTED\n", stack, input+itop);
            break;
        }

        char relation = table[stack_ind][input_ind];

        if(relation == '<' || relation == '='){
            printf("%s\t%s\tShift %c\n", stack, input+itop, input_curr);
            stack[++stop] = input_curr;
            stack[stop+1] = '\0';
            itop++;
        }
        else if(relation == '>'){
            printf("%s\t%s\tREDUCE\n", stack, input+itop);
            stack[stop--] = '\0';
        }
        else{
            printf("ERROR\n");
            break;
        }

    }

}
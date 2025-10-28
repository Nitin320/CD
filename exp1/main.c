#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

int is_keyword(const char *buffer);

int main()
{
    char ch, buffer[30];
    FILE *fp;
    int j = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) { 
        printf("Error opening file\n"); 
        return 1; 
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '#') {
            buffer[j++] = ch;
            while (isalpha(ch = fgetc(fp))) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0'; j = 0;
            ungetc(ch, fp); 
            printf("%s - Preprocessor directive\n", buffer);
        } 
        else if (ch == '<') {
            buffer[j++] = ch;
            while ((ch = fgetc(fp)) != '>') {
                buffer[j++] = ch;
            }
            buffer[j++] = '>';
            buffer[j] = '\0'; j = 0;
            printf("%s - Library\n", buffer);
        } 
        else if (isalpha(ch) || ch == '_') {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0'; j = 0;
            ungetc(ch, fp); 
            printf("%s - %s\n", buffer, is_keyword(buffer) ? "keyword" : "identifier");
        } 
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0'; j = 0;
            ungetc(ch, fp); 
            printf("%s - Number\n", buffer);
        } 
        else if (isspace(ch)) {
            continue;
        }
        else {
            switch (ch) {
                case '=': printf("= - Relational operator\n"); break;
                case ';':
                case ',': printf("%c - Separator\n", ch); break;
                case '(':
                case ')':
                case '{':
                case '}': printf("%c - Delimiter\n", ch); break;
            }
        }
    }

    fclose(fp);
    return 0;
}

int is_keyword(const char *buffer)
{
    const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default",
                              "do", "double", "else", "enum", "extern", "float", "for", "goto",
                              "if", "int", "long", "register", "return", "short", "signed",
                              "sizeof", "static", "struct", "switch", "typedef", "union",
                              "unsigned", "void", "volatile", "while", "printf"};
    
    for (int i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}
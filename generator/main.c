#include <stdio.h>
#include <string.h>
#include "../tokenizer/token.h"
#include "../isa/isa.h"

void print(char* string);
void emit(char byte);
int toInt(char* string);
float toFloat(char* string);

char output[5] = {};
int outputIndex = 0;

int main() {
    // FILE *fptr = fopen("sample", "r");
    // if(fptr == NULL) {
    //     printf("Could not open file!");
    //     return 1;
    // }

    // char text[1024];

    // fgets(text, 1024, fptr);
    // printf("%s", &text);

    // fclose(fptr);

    Token t = {"40", INTEGER};
    Token t1 = {"10", INTEGER};
    Token t2 = {"+", OPERATOR};
    Token tokens[] = {t, t1, t2};

    // Loop through each token, one by one.
    for(int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
        // Switch for each token type, emitting the instruction.
        switch(tokens[i].tokenType) {
            case INTEGER:
                printf("it was a integer: %s%c", tokens[i].val, 10);
                emit(PUSHINT);
                emit(toInt(tokens[i].val));
                break;
            case FLOAT:
                printf("it was a float: %s%c", tokens[i].val, 10);
                emit(PUSHFLOAT);
                emit(toFloat(tokens[i].val));
                break;
            case OPERATOR:
                printf("it was an operator: %s%c", tokens[i].val, 10);
                if(strcmp(tokens[i].val, "+") == 0) {
                    emit(ADD);
                }
                break;
            case LPAREN:
                print("it was a left parenthesis");
                break;
            case RPAREN:
                print("it was a right parenthesis");
                break;
        }
    }

    for(int byteIndex = 0; byteIndex < sizeof(output) / sizeof(output[0]); byteIndex++) {
        printf("%x%c", output[byteIndex], 10);
    }

    return 0;
}

void print(char* string) {
    printf("%s%c", string, 10);
}

void emit(char byte) {
    output[outputIndex] = byte;
    outputIndex = outputIndex + 1;
}

int toInt(char* string) {
    int i;
    sscanf(string, "%d", &i);
    return i;
}

float toFloat(char* string) {
    float i;
    sscanf(string, "%f", &i);
    return i;
}
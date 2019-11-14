#include <stdio.h>
#include <string.h>
#include "../tokenizer/token.h"
#include "../isa/isa.h"

void print(char* string);
void _emit(char byte);
void emit(char byte[], int size);
int toInt(char* string);
float toFloat(char* string);

char output[128] = {};
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

    // read in the data from the file

    FILE *readFile = fopen("tokens.bin", "rb");
    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile) / sizeof(Token);
    fseek(readFile, 0L, SEEK_SET);

    Token tokens[sz];

    fread(tokens, sizeof(Token), sizeof(tokens), readFile);

    fclose(readFile);

    remove("output");

    // Loop through each token, one by one.
    for(int i = sizeof(tokens) / sizeof(tokens[0]); i >= 0; i--) {
        // Switch for each token type, emitting the instruction.
        switch(tokens[i].tokenType) {
            case INTEGER:
                printf("it was a integer: %s%c", tokens[i].val, 10);
                int n = toInt(tokens[i].val);
                emit((char*)&n, 4);
                emit((char[]){PUSHINT}, 1);
                break;
            case FLOAT:
                printf("it was a float: %s%c", tokens[i].val, 10);
                float f = toFloat(tokens[i].val);
                emit((char*)&f, 4);
                emit((char[]){PUSHFLOAT}, 1);
                break;
            case OPERATOR:
                printf("it was an operator: %s%c", tokens[i].val, 10);
                if(strcmp(tokens[i].val, "+") == 0) {
                    emit((char[]){ADD}, 1);
                    break;
                }
                if(strcmp(tokens[i].val, "-") == 0) {
                    emit((char[]){SUB}, 1);
                    break;
                }
                if(strcmp(tokens[i].val, "/") == 0) {
                    emit((char[]){DIV}, 1);
                    break;
                }
                if(strcmp(tokens[i].val, "*") == 0) {
                    emit((char[]){MUL}, 1);
                    break;
                }
                if(strcmp(tokens[i].val, "**") == 0) {
                    emit((char[]){EXP}, 1);
                    break;
                }
                break;
        }
    }

    return 0;
}

void print(char* string) {
    printf("%s%c", string, 10);
}

void _emit(char byte) {
    output[outputIndex] = byte;
    outputIndex = outputIndex + 1;
}

void emit(char byte[], int size) {
    FILE* file = fopen("output", "ab");
    fwrite(byte, 1, size, file);
    for(int byteIndex = 0; byteIndex < size * sizeof(char); byteIndex++) {
        // if(output[byteIndex] == 0) {
        //     continue;
        // }
        printf("%hhx%c", byte[byteIndex], 10);
    }
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

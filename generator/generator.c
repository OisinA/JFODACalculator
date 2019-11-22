// Code Generator
// Takes an input of tokens in postfix form and outputs instructions into a file in byte format.
// Author: Oisin Aylward

#include <stdio.h>
#include <string.h>
#include "../tokenizer/token.h"
#include "../isa/isa.h"
#include "generator.h"

char output[128] = {};
int outputIndex = 0;

void generate(Token tokens[], int size) {
    // Loop through each token, one by one.
    for(int i = 0; i < size; ++i) {
        // Switch for each token type, emitting the instruction.
        switch(tokens[i].tokenType) {
            case INTEGER:
                printf("it was a integer: %s%c", tokens[i].val, 10);
                int n = toInt(tokens[i].val);
                emit((char[]){PUSHINT}, 1);
                emit((char*)&n, 4);
                break;
            case FLOAT:
                printf("it was a float: %s%c", tokens[i].val, 10);
                float f = toFloat(tokens[i].val);
                emit((char[]){PUSHFLOAT}, 1);
                emit((char*)&f, 4);
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
}

// print takes in a string and prints it, with a trailing new line character
void print(char* string) {
    printf("%s%c", string, 10);
}

// emit takes a byte array and its size and outputs it to an output file
void emit(char byte[], int size) {
    FILE* file = fopen("output", "ab");
    fwrite(byte, 1, size, file);
    for(int byteIndex = 0; byteIndex < size * sizeof(char); ++byteIndex) {
        printf("%hhx%c", byte[byteIndex], 10);
    }
    fclose(file);
}

// toInt converts a string to an integer
int toInt(char* string) {
    int i;
    sscanf(string, "%d", &i);
    return i;
}

// toFloat converts a string to a float
float toFloat(char* string) {
    float i;
    sscanf(string, "%f", &i);
    return i;
}

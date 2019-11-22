// Code Generator
// Takes an input of tokens in postfix form and outputs instructions into a file in byte format.
// Author: Oisin Aylward

#include <stdio.h>
#include "../tokenizer/token.h"
#include "../isa/isa.h"

void print(char* string);
void _emit(char byte);
void emit(char byte[], int size);
int toInt(char* string);
float toFloat(char* string);
void generate(Token tokens[], int size);
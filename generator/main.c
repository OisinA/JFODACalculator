// Code Generator
// Takes an input of tokens in postfix form and outputs instructions into a file in byte format.
// Author: Oisin Aylward

#include "../tokenizer/token.h"
#include "../isa/isa.h"
#include "generator.h"
#include <stdlib.h>

int main() {
    // read in the data from the file

    FILE *readFile = fopen("tokens.bin", "rb");
    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile) / sizeof(Token);
    rewind(readFile);

    Token* tokens = (Token*)malloc(sizeof(Token)*sz);

    fread(tokens, sizeof(Token), sizeof(tokens), readFile);

    fclose(readFile);

    remove("output");

    generate(tokens, sz);

    free(tokens);

    return 0;
}

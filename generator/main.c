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

    // Get size of file
    int sz = ftell(readFile) / sizeof(Token);
    rewind(readFile);

    // Create array of tokens
    Token* tokens = (Token*)malloc(sizeof(Token)*sz);

    // Read in tokens from file
    fread(tokens, sizeof(Token), sizeof(tokens), readFile);

    // Close the file
    fclose(readFile);

    // Remove an existing output file
    remove("output");

    // Generate the instructions and ouput to file
    generate(tokens, sz);

    // Release the memory allocated for tokens
    free(tokens);

    return 0;
}
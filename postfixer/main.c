#include <stdlib.h>
#include "../tokenizer/token.h"
#include "postfix.h"
#include <stdio.h>


// main function
int main() {

	// reads tokens from file
    FILE *readFile = fopen("tokens.bin", "rb");
    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile) / sizeof(Token);
    rewind(readFile);
    Token* tokens = (Token*)malloc(sizeof(Token)*sz);
    fread(tokens, sizeof(Token), sz, readFile);
    fclose(readFile);
    infix_to_postfix(tokens, sz);
    free(tokens);

    return 0;
}

// Main file for reading/writing of tokens
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include "token.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "token_readwrite.h"

// Write the tokens stored in the tokens array to a binary file.
// This binary file will contain all tokens tokenized from user input
// and can be read to retrieve the tokens by another file/module.
int writeTokensToFile(Token tokens[], int token_num) {
    // Write to a file.
    FILE* data;
    if ( (data = fopen("tokens.bin", "wb")) == NULL )
    {
        printf("There was an error when opening file.\n");
        return 1;
    }

    // Write the tokens to the file.
    fwrite(tokens, sizeof(Token) * token_num, 1, data);
    fclose(data);
    testReadingOfTokens();
    return 0;

}

void testReadingOfTokens() {
    printf("\nTesting Output Values ...");

    // read in the data from the file
    Token tokendata[100];

    FILE *readFile = fopen("tokens.bin", "rb");

    fread(tokendata, sizeof(Token), sizeof(tokendata), readFile);

    int j;

    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile);

    fseek(readFile, 0L, SEEK_SET);
    //printf("Size of file is %i", sz);

    for (j = 0; j < 3; j++) {
      Token token = tokendata[j];
      printf("\n### OUPUT VAL ###: VAL: %s TOKEN TYPE: %d\n", token.val, token.tokenType);
    }
}

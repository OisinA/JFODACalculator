#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"

int isoperator(char c);
int writeTokensToFile(void);

// Create a global token struct variable.
Token token;

// Array of tokens. Upper limit set to 100 for now.
Token tokens[100];

int main(int argc, char **argv) {
  char expr[100];
  printf("Enter an expression: \n");
  scanf("%[^\n]s", expr);

  size_t i = 0;

  // index into the tokens array.
  size_t tokens_i = 0;
  int str_len = strlen( expr );

  // Iterate over every char in the string
  for (i = 0; i < str_len; i++){

    char c = expr[i];

    printf("\nOn character %c\n", c);

    // check if it's a number
    if (isdigit(c)) {
      printf("Is a digit.");
      token.tokenType = INTEGER;
    }

    // check if it's an operand
    // create an operator token
    else if (isoperator(c) == 1) {
      token.tokenType = OPERATOR;
    }

    // Check if it's a left parenthesis.
    else if (c == '(') {
      token.tokenType = LPAREN;
    }

    // Check if it's a right parenthesis.
    else if (c == ')') {
      token.tokenType = RPAREN;
    }
    // Disregard this character; it is neither an operator or num
    else {
      continue;
    }

    strcpy( token.val, &c );
    printf("\n### NEW TOKEN ###: %c\n", c);
    printf("\nTOKEN VAL: %s\nTOKEN TYPE: %u\n", token.val, token.tokenType);
    tokens[tokens_i] = token;
    tokens_i += 1;
}

writeTokensToFile();
}

// Write the tokens stored in the tokens array to a binary file.
// This binary file will contain all tokens tokenized from user input
// and can be read to retrieve the tokens by another file/module.
int writeTokensToFile() {
    // Write to a file.
    FILE* data;
    if ( (data = fopen("tokens.bin", "wb")) == NULL )
    {
        printf("There was an error when opening file\n");
        return 1;
    }

     // Write the tokens to the file.
    fwrite(tokens, sizeof(Token) * 100, 1, data);
    fclose(data);

    testReadingOfTokens();
}

void testReadingOfTokens() {
    printf("Testing Output Values ...");

    // read in the data from the file
    Token tokendata[100];

    FILE *readFile = fopen("tokens.bin", "rb");

    fread(tokendata, sizeof(Token), sizeof(tokendata), readFile);

    int j;
    for (j = 0; j < 3; j++) {
      Token token = tokendata[j];
      printf("\n### OUPUT VAL ###: %d VAL: %s\n", token.tokenType, token.val);
    }
}

// Check if a character is an operator.
// Returns 1 if true, 0 if false.
int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*') {
    return 1;
  }
  return 0;
}

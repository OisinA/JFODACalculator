#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"

int isoperator(char c);

Token token;
Token tokens[100];

int main(int argc, char **argv) {
  char expr[100];
  printf("Enter an expression: \n");
  scanf("%[^\n]s", expr);

  size_t i = 0;
  int str_len = strlen( expr );
  
  // Iterate over every char in the string
  for (i = 0; i < str_len; i++){

    char c = expr[i];
    Token token = {c, OPERATOR};
    // check if it's a number
    if (isdigit(c)){
      printf("Num Token: %c\n", c);
      token.tokenType = INTEGER;
    }

    // check if it's an operand
    // create an operator token
    else if (isoperator(c) == 1) {
      printf("Op Token: %c\n", c);
      token.tokenType = OPERATOR;
    }

    // Check if it's a left parenthesis.
    else if (c == '(') {
      printf("LPAREN Token: %c\n", c);
      token.tokenType = LPAREN;
    }

    // Check if it's a right parenthesis.
    else if (c == ')') {
      printf("RPAREN Token: %c\n", c);
      token.tokenType = RPAREN;
    }
    // Disregard this character; it is neither an operator or num
    else {
      continue;
    }
    printf("##\nTOKEN VAL: %s\nTOKEN TYPE: %u\n", token.val, token.tokenType);
    tokens[i] = token;

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
    }
}

int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*') {
    return 1;
  }
  return 0;
}


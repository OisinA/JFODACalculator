#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"

int isoperator(char c);

// Create a global token struct variable.
Token token;

// Array of tokens. Upper limit set to 100 for now.
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

    // Create a token struct. It's assigned the token type of operator for now, until I 
    // patch this.
    Token token = {c, OPERATOR};

    // check if it's a number
    if (isdigit(c)){
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
    printf("\n### NEW TOKEN ###: %c\n", c);
    printf("\nTOKEN VAL: %s\nTOKEN TYPE: %u\n", token.val, token.tokenType);
    tokens[i] = token;
}
}

int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*') {
    return 1;
  }
  return 0;
}


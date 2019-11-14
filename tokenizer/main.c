#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"
#include "token_readwrite.h"

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

  // index into the tokens array.
  size_t tokens_i = 0;
  int str_len = strlen( expr );

  // Iterate over every char in the string

  while (i < str_len){
    char nums[10] = { NULL };
    char c = expr[i];
    int k = 0;

    // check if it's a number
    if (isdigit(c)) {
      token.tokenType = INTEGER;
      size_t m = 0;

      while (isdigit(expr[i]) || expr[i] == '.') {
        if (expr[i] == '.') {
          token.tokenType = FLOAT;
        }
        c = expr[i];

        // convert the char to an int
        nums[m] = c;

        i++;
        m++;
      };

      i--;

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

    else if (c == '.') {
      i++;

    }
    // Disregard this character; it is neither an operator or num
    else {
      i++;
      continue;
    }

    if (token.tokenType == INTEGER || token.tokenType == FLOAT) {
      char b = k;
      strcpy(token.val, &nums);
    }

    else {
      strcpy( token.val, &c );
    }

    printf("\nEXPORTED TOKEN: %s %u", token.val, token.tokenType);

    tokens[tokens_i] = token;
    tokens_i += 1;
    i++;
}

writeTokensToFile(tokens);
}



// Check if a character is an operator.
// Returns 1 if true, 0 if false.
int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*') {
    return 1;
  }
  return 0;
}

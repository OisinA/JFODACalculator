#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"
#include "token_readwrite.h"

// index into the tokens array.
size_t tokens_i = 0;

// Create a global token struct variable.
Token token;

// Array of tokens. Upper limit set to 100 for now.
Token tokens[100];

const char *TokenNames[] = {"INTEGER", "FLOAT", "OPERATOR", "LPAREN", "RPAREN"};

void tokenize(char *expr) {
  size_t i = 0;

  int str_len = strlen( expr );

  // Iterate over every char in the string
  while (i < str_len) {

    char nums[128] = { 0 };
    char c = expr[i];

    // check if it's a number
    if (isdigit(c)) {
      token.tokenType = INTEGER;
      size_t m = 0;

      while (isdigit(expr[i]) || expr[i] == '.') {
        if (expr[i] == '.') {
          token.tokenType = FLOAT;
        }
        c = expr[i];

        // append the char to the nums array
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

    // Disregard this character; it is neither an operator or num
    else {
      i++;
      continue;
    }

    if (token.tokenType == INTEGER || token.tokenType == FLOAT) {
      strcpy(token.val, nums);
    }

    // Token is either a parenthesis or an operator
    else {
      c = expr[i];
      strcpy( token.val, &c );
      token.val[1] = '\0';
    }

    exportToken();
    i++;
  }

  writeTokensToFile(tokens, tokens_i);
}

// Save the token in the tokens array and increment the current token index
void exportToken() {

  printf("EXPORTED TOKEN -> %s %s\n", token.val, TokenNames[token.tokenType]);

  tokens[tokens_i] = token;
  tokens_i += 1;
}

// Check if a character is an operator.
// Returns 1 if true, 0 if false.
int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*') {
    return 1;
  }
  return 0;
}

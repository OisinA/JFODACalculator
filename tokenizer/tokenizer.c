// File for tokenizer component, which takes an arithmetical expression
// and writes the array of tokens to a file.
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

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

const char *TokenNames[] = {"INTEGER", "FLOAT", "OPERATOR", "LPAREN", "RPAREN"};

Token *tokenize(char *expr) {
  Token *tokens = malloc(sizeof(Token) * 100);

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

    // Append the token to the tokens array.
    exportToken(tokens);
    i++;
  }

  // Write the array of tokens to a file.
  writeTokensToFile(tokens, tokens_i);
}

void exportToken(Token *tokens) {

  printf("EXPORTED TOKEN -> %s %s\n", token.val, TokenNames[token.tokenType]);

  tokens[tokens_i] = token;
  tokens_i += 1;
}

int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^') {
    return 1;
  }
  return 0;
}

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

// Tokenizes an arithmetical expression.
// returns a Result struct containing an array of tokens and
// the num of tokens in the array.
Result tokenize(char *expr) {
  Token *tokens = malloc(sizeof(Token) * 100);

  size_t i = 0;

  int str_len = strlen( expr );

  // Iterate over every char in the string
  while (i < str_len) {

    // initialize an array of numbers.
    char nums[128] = { 0 };

    // get the current character in the expression.
    char c = expr[i];

    // check if it's a number
    if (isdigit(c)) {
      token.tokenType = INTEGER;
      size_t num_i = 0;

      while (isdigit(expr[i]) || expr[i] == '.') {
        if (expr[i] == '.') {
          token.tokenType = FLOAT;
        }
        c = expr[i];

        // append the char to the nums array
        nums[num_i] = c;

        i++;
        num_i++;
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
  Result result = { tokens, tokens_i};

  return result;
}

// Append the token to the tokens array.
void exportToken(Token *tokens) {

  printf("EXPORTED TOKEN -> %s %s\n", token.val, TokenNames[token.tokenType]);

  tokens[tokens_i] = token;
  tokens_i += 1;
}

// Check if a character is an operator.
// An operator is either one of the following: + - / *
// returns an int; 1 if true, 0 if false.
int isoperator(char c) {
  if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^') {
    return 1;
  }
  return 0;
}

// Check if two token arrays are equal.
int token_array_is_equal(Token *array_one, Token *array_two,
                    const size_t elem_size, const size_t elem_count) {
  int is_equal = 0;

  for (int i = 0; i < elem_count; i++) {
    Token token1 = array_one[i];
    Token token2 = array_two[i];
    printf("\nToken1: Val -> %sToken2: Val -> %s", token1.val, token2.val);
    printf("\nToken1: Type -> %dToken2: Type -> %d", token1.tokenType, token2.tokenType);

    if (strcmp(token1.val, token2.val) != 0 || token1.tokenType != token2.tokenType) {
      is_equal = 1;
      break;
    }

  }
  return is_equal;

}

// Free the memory associated with the token array.
void freeTokens(Result result) {
  free(result.tokens);
}

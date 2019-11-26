// Main file to tokenize an arithmetical expression
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "io.h"
#include "token.h"
#include "token_readwrite.h"

int main(int argc, char **argv) {
  // Read the input file
  char* expr = readFile();

  // If the file does not exist, return an error.
  if (!expr) {
    printf("Error: Couldn't parse file");
    return -1;
  }

  // Tokenize the arithmetical expression
  Result result = tokenize(expr);

  // Write the token array to a file.
  writeTokensToFile(result.tokens, result.token_num);

  // Free the memory associated with the tokens.
  freeTokens(result);
}

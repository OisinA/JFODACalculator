// Main file to tokenize an arithmetical expression
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "io.h"

int main(int argc, char **argv) {
  char* expr = readFile();

  if (!expr) {
    printf("Error: Couldn't parse file");
    return -1;
  }

  tokenize(expr);
}

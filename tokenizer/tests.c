// Author: Silvia O'Dwyer
// Student Number: 117333306
// Tests for the tokenizer component.
// These tests include the testing of the correct reading of the input file,
// as well as the correct tokenizing of the arithmetical expression.

#include <ctap.h>
#include "token_readwrite.h"
#include "io.c"
#include <stdio.h>
#include <string.h>

TESTS {
  // test file input
  subtest {
    // read in the file into the expression.
    char* expr = readFile();
    // remove new line from expression.
    strtok(expr, "\n");

    char correct_expr[100] = "(1.3 + 4.5 * 7) - 2";

    ok(strcmp(expr, correct_expr) == 0, "arithmetical expression from file equal to string" );
  }

  // test tokenization
  subtest {

  }
}

// gcc -o test.t tests.c # compile file test.c, generating test.t as executable output.
// prove ./*.t

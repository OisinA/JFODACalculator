// Author: Silvia O'Dwyer
// Student Number: 117333306
// Tests for the tokenizer component.
// These tests include the testing of the correct reading of the input file,
// as well as the correct tokenizing of the arithmetical expression.

#include <ctap.h>
#include "token_readwrite.h"
#include "tokenizer.h"
#include "io.h"
#include "token.h"
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
    char* expr = readFile();
    // remove new line from expression.
    strtok(expr, "\n");

    Token correct_tokens[] = {{"(", 3}, {"1.3", 1}, {"+", 2}, {"4.5", 1}, {"*", 2}, {"7", 0}, {")", 4}, {"-", 2}, {"2", 0}};

    // Tokenize the expression
    Result result = tokenize(expr);
    Token *tokens = result.tokens;
    ok(token_array_is_equal(correct_tokens, tokens, sizeof(Token), 9) == 0, "Two array of tokens are equal.");
  }
}



// gcc -o test.t tests.c # compile file test.c, generating test.t as executable output.
// prove ./*.t

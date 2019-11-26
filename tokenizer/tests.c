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
  // test tokenization
  subtest {
    char* expr1 = "(1.3 + 4.5 * 7) - 2";
    // remove new line from expression.

    Token correct_tokens[] = {{"(", 3}, {"1.3", 1}, {"+", 2}, {"4.5", 1}, {"*", 2}, {"7", 0}, {")", 4}, {"-", 2}, {"2", 0}};

    // Tokenize the expression
    Result result1 = tokenize(expr1);
    Token *tokens1 = result1.tokens;
    ok( token_array_is_equal(correct_tokens, result1.tokens, sizeof(correct_tokens), result1.token_num) == 0, "Both token arrays are equal.");

  }
  // test tokenization of input with extraneous/illegal characters
  subtest {
        Token correct_tokens[] = {{"(", 3}, {"1.3", 1}, {"+", 2}, {"4.5", 1}, {"*", 2}, {"7", 0}, {")", 4}, {"-", 2}, {"2", 0}};

        // Second test using input with illegal characters.
        char* expr2 = "(1.3 + 4.5 * 7) - 2& ;";
        strtok(expr2, "\n");
        Result result2 = tokenize(expr2);
        ok( token_array_is_equal(correct_tokens, result2.tokens, sizeof(correct_tokens), result2.token_num) == 0, "Token arrays are equal.");

        // Third test using extraneous white space
        char* expr3 = "      (1.3 + 4.5 * 7) - 2 ";
        Result result3 = tokenize(expr3);
        Token *tokens3 = result3.tokens;
        ok( token_array_is_equal(correct_tokens, tokens3, sizeof(correct_tokens), result3.token_num) == 0, "Token arrays are equal.");
  }
}

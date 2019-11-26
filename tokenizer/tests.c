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

    Token correct_tokens[] = {{"(", 3}, {"1.3", 1}, {"+", 2}, {"4.5", 1}, {"*", 2}, {"7", 0}, {")", 4}, {"-", 2}, {"2", 0}};

    // Tokenize the expression
    Result result1 = tokenize(expr1);
    Token *tokens1 = result1.tokens;
    ok( token_array_is_equal(correct_tokens, result1.tokens, sizeof(correct_tokens), result1.token_num) == 0, "Both token arrays are equal. Input contains operators, parens, ints and floats.");

    // Test all operators, and include both integers and floating point numbers
    char* expr2 = "1 + 2.5 - 3 * 9 / 4.3 ^ 2";
    Token correct_tokens2[] = {{"1", 0}, {"+", 2}, {"2.5", 1}, {"-", 2}, {"3", 0}, {"*", 2}, {"9", 0}, {"/", 2}, {"4.3", 1}, {"^", 2}, {"2", 0}};
    Result result2 = tokenize(expr2);
    Token *tokens2 = result2.tokens;
    ok( token_array_is_equal(correct_tokens2, result2.tokens, sizeof(correct_tokens2), result2.token_num) == 0, "Both token arrays are equal. Input contains operators, parens, ints, floats, and the exponent operator.");

    // Third test which contains ints, float numbers, operators, and left and right brackets
    char* expr3 = "(1 + 2.5) - (3 * 10)";
    Token correct_tokens3[] = {{"(", 3}, {"1", 0}, {"+", 2}, {"2.5", 1}, {")", 4}, {"-", 2}, {"(", 3}, {"3", 0}, {"*", 2}, {"10", 0}, {")", 4},};
    Result result3 = tokenize(expr3);
    Token *tokens3 = result3.tokens;
    ok( token_array_is_equal(correct_tokens3, result3.tokens, sizeof(correct_tokens3), result3.token_num) == 0, "Both token arrays are equal. Input contains ints, floats, operators, and parens.");

    // Fourth test containing all possible token types.
    char* expr4 = "(1 + 2.5 - 3 * 1.2 / 4 + 3) ^ 2";
    Token correct_tokens4[] = {{"(", 3}, {"1", 0}, {"+", 2}, {"2.5", 1}, {"-", 2}, {"3", 0}, {"*", 2}, {"1.2", 1}, {"/", 2},
                              {"4", 0}, {"+", 2}, {"3", 0}, {")", 4}, {"^", 2}, {"2", 0}};
    Result result4 = tokenize(expr4);
    Token *tokens4 = result4.tokens;
    ok( token_array_is_equal(correct_tokens4, result4.tokens, sizeof(correct_tokens4), result4.token_num) == 0, "Both token arrays are equal. Input contains all token types.");

    // Fifth test with no whitespace, and containing integers and operators.
    char* expr5 = "(1+2)-(5*3)";
    Token correct_tokens5[] = {{"(", 3}, {"1", 0}, {"+", 2}, {"2", 0}, {")", 4}, {"-", 2}, {"(", 3}, {"5", 0}, {"*", 2}, {"3", 0}, {")", 4}};
    Result result5 = tokenize(expr5);
    Token *tokens5 = result5.tokens;
    ok( token_array_is_equal(correct_tokens5, result5.tokens, sizeof(correct_tokens5), result5.token_num) == 0, "Both token arrays are equal. Input contains all token types.");


  }
  // test tokenization of input with extraneous/illegal characters
  subtest {
        Token correct_tokens[] = {{"(", 3}, {"1.3", 1}, {"+", 2}, {"4.5", 1}, {"*", 2}, {"7", 0}, {")", 4}, {"-", 2}, {"2", 0}};

        // Sixth test using input with illegal characters.
        char* expr6 = "(1.3 + 4.5 * 7) - 2& ;";
        strtok(expr6, "\n");
        Result result6 = tokenize(expr6);
        ok( token_array_is_equal(correct_tokens, result6.tokens, sizeof(correct_tokens), result6.token_num) == 0, "Token arrays are equal. Input contains illegal chars.");

        // Eight test using extraneous white space
        char* expr7 = "      (1.3 + 4.5 * 7) - 2 ";
        Result result7 = tokenize(expr7);
        Token *tokens7 = result7.tokens;
        ok( token_array_is_equal(correct_tokens, tokens7, sizeof(correct_tokens), result7.token_num) == 0, "Token arrays are equal. Input contains extraneous whitespace.");

        // Ninth test using illegal characters, extraneous whitespace, and all token types.
        char* expr8 = "    (1 + 2.5 - 3 * 1.2 /   4 + 3) ^ 2    ;";
        Token correct_tokens8[] = {{"(", 3}, {"1", 0}, {"+", 2}, {"2.5", 1}, {"-", 2}, {"3", 0}, {"*", 2}, {"1.2", 1}, {"/", 2},
                                  {"4", 0}, {"+", 2}, {"3", 0}, {")", 4}, {"^", 2}, {"2", 0}};
        Result result8 = tokenize(expr8);
        Token *tokens8 = result8.tokens;
        ok( token_array_is_equal(correct_tokens8, tokens8, sizeof(correct_tokens8), result8.token_num) == 0, "Token arrays are equal. Input contains extraneous whitespace, illegal chars, and all token types.");


  }
}

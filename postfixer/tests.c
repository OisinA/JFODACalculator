// tests for postfixer
// Author: Michael Forde
// Student Number: 117392626
// Extra: DSS, I have a spelling and grammer waver

#include <ctap.h>
#include "postfix.c"
#include "../tokenizer/token.h"

TESTS {
    // Test adding
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be outputted
        Token t0 = {"1", INTEGER};
        Token t1 = {"+", OPERATOR};
        Token t2 = {"2", INTEGER};
        Token tokens[] = {t0, t1, t2};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens, 3);

        // read in created list of tokens
        FILE *readFile = fopen("tokens.bin", "rb");
        fseek(readFile, 0L, SEEK_END);
        int sz = ftell(readFile) / sizeof(Token);
        rewind(readFile);
        Token* tokens = (Token*)malloc(sizeof(Token)*sz);
        fread(tokens, sizeof(Token), sizeof(tokens), readFile);
        fclose(readFile);

        // Make an array containing the expected tokens
        Token expected[] = {t0, t2, t1};

        // Loop through the tokens to ensure there correct
        for(int i = 0; i < sz; ++i) {
            ok(tokens[i] == expected[i], "%d: int instructions as expected %x %x", i, tokens[i], expected[i]);
        }

        free(tokens);
    }

    // Test multiplications
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be outputted
        Token t0 = {"1", INTEGER};
        Token t1 = {"*", OPERATOR};
        Token t2 = {"2", INTEGER};
        Token tokens[] = {t0, t1, t2};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens, 3);

        // read in created list of tokens
        FILE *readFile = fopen("tokens.bin", "rb");
        fseek(readFile, 0L, SEEK_END);
        int sz = ftell(readFile) / sizeof(Token);
        rewind(readFile);
        Token* tokens = (Token*)malloc(sizeof(Token)*sz);
        fread(tokens, sizeof(Token), sizeof(tokens), readFile);
        fclose(readFile);

        // Make an array containing the expected tokens
        Token expected[] = {t0, t2, t1};

        // Loop through the tokens to ensure there correct
        for(int i = 0; i < sz; ++i) {
            ok(tokens[i] == expected[i], "%d: int instructions as expected %x %x", i, tokens[i], expected[i]);
        }

        free(tokens);
    }

    // Test testing parenthesis
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be tested, this would will be most complicated
        Token t0 = {"1", INTEGER};
        Token t1 = {"+", OPERATOR};
        Token t2 = {"2", INTEGER};
        Token t3 = {"-", OPERATOR};
        Token t4 = {"(", LPAREN};
        Token t5 = {"2", INTEGER};
        Token t6 = {"+", INTEGER};
        Token t7 = {"2", INTEGER};
        Token t8 = {")", RPAREN};
        Token tokens[] = {t0, t1, t2, t3, t4, t5, t6, t7, t8};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens, 9);

        // read in created list of tokens
        FILE *readFile = fopen("tokens.bin", "rb");
        fseek(readFile, 0L, SEEK_END);
        int sz = ftell(readFile) / sizeof(Token);
        rewind(readFile);
        Token* tokens = (Token*)malloc(sizeof(Token)*sz);
        fread(tokens, sizeof(Token), sizeof(tokens), readFile);
        fclose(readFile);

        // Make an array containing the expected tokens
        Token expected[] = {t0, t2, t1, t5, t7, t6, t3};

        // Loop through the tokens to ensure there correct
        for(int i = 0; i < sz; ++i) {
            ok(tokens[i] == expected[i], "%d: int instructions as expected %x %x", i, tokens[i], expected[i]);
        }

        free(tokens);
    }
}
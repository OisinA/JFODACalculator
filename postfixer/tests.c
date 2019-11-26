// tests for postfixer
// Author: Michael Forde
// Student Number: 117392626
// Extra: DSS, I have a spelling and grammer waver

#include <ctap.h>
#include "postfix.h"
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
        Token tokens_in[] = {t0, t1, t2};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 3);

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
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
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
        Token tokens_in[] = {t0, t1, t2};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 3);

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
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
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
        Token tokens_in[] = {t0, t1, t2, t3, t4, t5, t6, t7, t8};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 9);

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
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
        }

        free(tokens);
    }

    // Test parenthesis
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be tested, this would will be most complicated
        Token t0 = {"(", LPAREN};
        Token t1 = {"6", INTEGER};
        Token t2 = {"*", OPERATOR};
        Token t3 = {"8", INTEGER};
        Token t4 = {")", RPAREN};
        Token t5 = {"5", INTEGER};
        Token t6 = {"/", OPERATOR};
        Token t7 = {"2", INTEGER};
        Token tokens_in[] = {t0, t1, t2, t3, t4, t5, t6, t7};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 8);

        // read in created list of tokens
        FILE *readFile = fopen("tokens.bin", "rb");
        fseek(readFile, 0L, SEEK_END);
        int sz = ftell(readFile) / sizeof(Token);
        rewind(readFile);
        Token* tokens = (Token*)malloc(sizeof(Token)*sz);
        fread(tokens, sizeof(Token), sizeof(tokens), readFile);
        fclose(readFile);

        // Make an array containing the expected tokens
        Token expected[] = {t1, t3, t2, t5, t7, t6};

        // Loop through the tokens to ensure there correct
        for(int i = 0; i < sz; ++i) {
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
        }

        free(tokens);
    }

    // Test Floats and devides
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be tested, this would will be most complicated
        Token t0 = {"3.65", FLOAT};
        Token t1 = {"*", OPERATOR};
        Token t2 = {"0.98", FLOAT};
        Token t3 = {"/", OPERATOR};
        Token t4 = {"(", LPAREN};
        Token t5 = {"5", INTEGER};
        Token t6 = {"+", OPERATOR};
        Token t7 = {"3", INTEGER};
        Token t8 = {")", RPAREN};

        Token tokens_in[] = {t0, t1, t2, t3, t4, t5, t6, t7, t8};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 9);

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
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
        }

        free(tokens);
    }

    // Test powers and floats
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be tested, this would will be most complicated
        Token t0 = {"(", LPAREN};
        Token t1 = {"4", INTEGER};
        Token t2 = {"*", OPERATOR};
        Token t3 = {"3.1415", FLOAT};
        Token t4 = {")", RPAREN};
        Token t5 = {"^", OPERATOR};
        Token t6 = {"2", INTEGER};

        Token tokens_in[] = {t0, t1, t2, t3, t4, t5, t6};

        // convert tokens from infix to postfix
        infix_to_postfix(tokens_in, 5);

        // read in created list of tokens
        FILE *readFile = fopen("tokens.bin", "rb");
        fseek(readFile, 0L, SEEK_END);
        int sz = ftell(readFile) / sizeof(Token);
        rewind(readFile);
        Token* tokens = (Token*)malloc(sizeof(Token)*sz);
        fread(tokens, sizeof(Token), sizeof(tokens), readFile);
        fclose(readFile);

        // Make an array containing the expected tokens
        Token expected[] =  {t1, t3, t2, t6, t5};

        // Loop through the tokens to ensure there correct
        for(int i = 0; i < sz; ++i) {
            ok(tokens[i].tokenType == expected[i].tokenType, "Test %d: Expected %s but got %s", i, expected[i].val, tokens[i].val);
        }

        free(tokens);
    }

}

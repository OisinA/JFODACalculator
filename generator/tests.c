#include <ctap.h>
#include "generator.h"
#include "../tokenizer/token.h"
#include "../isa/isa.h"

TESTS {
    // Test integers
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be outputted
        Token t = {"40", INTEGER};
        Token t1 = {"10", INTEGER};
        Token t2 = {"+", OPERATOR};
        Token tokens[] = {t, t1, t2};

        // Generate ISA and output to file
        generate(tokens, 3);

        // Read in the generated file as an array of Tokens
        FILE* fp = fopen("output", "r");
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        char instructions[size];
        rewind(fp);
        fread(instructions, size, 1, fp);

        // Make an array containing the expected output
        char expected_output[] = {
            PUSHINT,
            (char) 40,
            (char) 0,
            (char) 0,
            (char) 0,
            PUSHINT,
            (char) 10,
            (char) 0,
            (char) 0,
            (char) 0,
            ADD,
        };

        // Loop through the instructions ensuring they are the same as expected
        for(int i = 0; i < size; ++i) {
            ok(instructions[i] == expected_output[i], "%d: int instructions as expected %x %x", i, instructions[i], expected_output[i]);
        }
    }

    // Test floats
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be outputted
        Token t = {"40.2", FLOAT};
        Token t1 = {"10.5", FLOAT};
        Token t2 = {"+", OPERATOR};
        Token tokens[] = {t, t1, t2};

        // Generate ISA and output to file
        generate(tokens, 3);

        // Read in the generated file as an array of Tokens
        FILE* fp = fopen("output", "r");
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        char instructions[size];
        rewind(fp);
        fread(instructions, size, 1, fp);

        // Make an array containing the expected output
        char expected_output[] = {
            PUSHFLOAT,
            (char) -51,
            (char) -52,
            (char) 32,
            (char) 66,
            PUSHFLOAT,
            (char) 0,
            (char) 0,
            (char) 40,
            (char) 65,
            ADD,
        };

        // Loop through the instructions ensuring they are the same as expected
        for(int i = 0; i < size; ++i) {
            ok(instructions[i] == expected_output[i], "%d: float instructions as expected %d %d", i, instructions[i], expected_output[i]);
        }
    }

    // Test integers and floats
    subtest {
        // Remove old output file
        remove("output");

        // Create tokens to be outputted
        Token t = {"40", INTEGER};
        Token t1 = {"10.5", FLOAT};
        Token t2 = {"+", OPERATOR};
        Token tokens[] = {t, t1, t2};

        // Generate ISA and output to file
        generate(tokens, 3);

        // Read in the generated file as an array of Tokens
        FILE* fp = fopen("output", "r");
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        char instructions[size];
        rewind(fp);
        fread(instructions, size, 1, fp);

        // Make an array containing the expected output
        char expected_output[] = {
            PUSHINT,
            (char) 40,
            (char) 0,
            (char) 0,
            (char) 0,
            PUSHFLOAT,
            (char) 0,
            (char) 0,
            (char) 40,
            (char) 65,
            ADD,
        };

        // Loop through the instructions ensuring they are the same as expected
        for(int i = 0; i < size; ++i) {
            ok(instructions[i] == expected_output[i], "%d: float/int instructions as expected %d %d", i, instructions[i], expected_output[i]);
        }
    }
}
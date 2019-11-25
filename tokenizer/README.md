# Tokenizer

The tokenizer reads in an arithmetical expression from a file, identifies the tokens
and their types, and exports these tokens by writing them to an array in a file.

## Running

To run the tokenizer, an input file called `test.txt` is required,
which contains an arithmetical expression on the first line.
The input file has been included in this directory.

Then to compile the code: `gcc main.c`

To execute: `./a.out`

### Output
Output: Tokens are added to an array as they are identified. This array
is then written to a binary file called `tokens.bin`.

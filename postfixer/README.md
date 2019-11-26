# Infix to Postfix

The infix to postfix reads in a `tokens.bin` file which contains an array of tokens representing
a infix mathimatical equation, then it loops though each token and rearranges them to postfix notation.

## Running

In order to run postfixer you must have an equation created by the tokenizer in a file called
`tokens.bin`.

Then to compile the code: `gcc main.c`

To execute: `./a.out`

### Output

Output: Postfix tokens are added to an array. This array
is then written to a binary file called `tokens.bin`.

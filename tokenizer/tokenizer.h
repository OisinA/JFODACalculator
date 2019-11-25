// Header file for tokenizer
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306
#include "token.h"

#ifndef __TOKENIZER__
#define __TOKENIZER__

 // Check if a character is an operator.
 // An operator is either one of the following: + - / *
// returns: an int. 1 if true, 0 if false.
int isoperator(char c);


// Append the token to the tokens array.
void exportToken();

// Tokenizes an arithmetical expression.
// an array of Tokens.
Result tokenize(char *expr);

int token_array_is_equal(Token *array_one, Token *array_two,
                    const size_t elem_size, const size_t elem_count);

#endif

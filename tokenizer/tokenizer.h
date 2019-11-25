// Header file for tokenizer
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306
#include "token.h"

#ifndef __TOKENIZER__
#define __TOKENIZER__

/*
 * Function:  isoperator
 * --------------------
 * Check if a character is an operator.
 * An operator is either one of the following: + - / *
 *
 *  c: character to check
 *  returns: an int. 1 if true, 0 if false.
 */
int isoperator(char c);

/*
 * Function:  exportToken
 * --------------------
 * Append the token to the tokens array.
 *
 */
void exportToken();

/*
 * Function:  tokenize
 * --------------------
 * Tokenizes an arithmetical expression.
 *
 * *expr: Expression to tokenize
 *  Writes an array of tokens to an output file called tokens.bin
 */
Token *tokenize(char *expr);

#endif

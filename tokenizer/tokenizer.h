// Header file for tokenizer
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306
#include "token.h"

#ifndef __TOKENIZER__
#define __TOKENIZER__

int isoperator(char c);
void exportToken();
Result tokenize(char *expr);
int token_array_is_equal(Token *array_one, Token *array_two,
                    const size_t elem_size, const size_t elem_count);
void freeTokens(Result result);

#endif

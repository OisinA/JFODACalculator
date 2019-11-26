// Header file for reading/writing of tokens
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include "token.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __TOKEN_READ_WRITE__
#define __TOKEN_READ_WRITE__

int writeTokensToFile(Token tokens[], int token_num);
void printTokenArray();

#endif

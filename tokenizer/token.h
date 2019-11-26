// Header file for token and result structs, as well as TokenType enum
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include <stddef.h>

#ifndef __TOKEN_H__
#define __TOKEN_H__

typedef enum {
	INTEGER,
	FLOAT,
	OPERATOR,
	LPAREN,
	RPAREN,
} TokenType;

typedef struct {
	char val[128];
  TokenType tokenType;
} Token;

typedef struct {
	Token *tokens;
	size_t token_num;
} Result;

#endif

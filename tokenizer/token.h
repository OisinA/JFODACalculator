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

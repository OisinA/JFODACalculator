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

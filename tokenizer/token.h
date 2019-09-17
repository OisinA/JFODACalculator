typedef enum TokenType {
	INTEGER,
	FLOAT,
	OPERATOR,
	LPAREN,
	RPAREN,
};

typedef struct Token {
	char val[128];
    	TokenType tokenType;
};

typedef enum TokenType {
	INTEGER,
	FLOAT,
	OPERATOR,
	LPAREN,
	RPAREN,
};

struct Token {
	char val[128];
    	TokenType tokenType;
};

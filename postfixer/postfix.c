// standard libs
#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// local libs
#include "../tokenizer/token.h"
#include "../tokenizer/token_readwrite.h"

// Stack used to store postfix tokenression
struct Stack {
	int top;
	unsigned capacity;
	Token* array;
};

// Stack Operations
struct Stack* create_stack( unsigned capacity ) {
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

	if (!stack)
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (int*) malloc(stack->capacity * sizeof(int));

	if (!stack->array)
		return NULL;
	return stack;
}

// check if stack is empty
int is_empty(struct Stack* stack) {
	return stack->top == -1 ;
}

// check item at top of stack
Token peek(struct Stack* stack) {
	return stack->array[stack->top];
}

// pop item off top of stack
Token pop(struct Stack* stack) {
	return stack->array[stack->top--];
}

// push item onto top of stack
void push(struct Stack* stack, Token item) {
	stack->array[++stack->top] = item;
}


// check if the given character is operand
int is_operand(Token token) {
	if (token.tokenType == OPERATOR){
		return 1;
	}
	return 0;
}

// returns importance of a given operator
int operator(Token token) {
	if (token.val == '+' || token.val == '-') {
		return 1;
	}
	if (token.val == '*' || token.val == '/') {
		return 2;
	}

	return -1;
}


// converts infix to postfix
int infix_to_postfix(Token* tokens, int size) {
	int i, k;

	// creates a stack of capacity equal to tokenression size
	struct Stack* stack = create_stack(size);
	if(!stack)
		return -1 ;

	for (i = 0, k = -1; i < size; ++i) {
		// if the character is an operand, add it to output.
		if (is_operand(tokens[i]))
			tokens[++k] = tokens[i];

		// if the character is an ‘(‘, push it to the stack.
		else if (tokens[i].tokenType == LPAREN)
			push(stack, tokens[i]);

		// if the character is an ‘)’, pop and output from the stack
		// until an ‘(‘ is encountered.
		else if (tokens[i].tokenType == RPAREN) {
			while (!is_empty(stack) && peek(stack).tokenType != LPAREN)
				tokens[++k] = pop(stack);
			if (!is_empty(stack) && peek(stack).tokenType != LPAREN)
				return -1;
			else
				pop(stack);
		}
		else {
			while (!is_empty(stack) && operator(tokens[i]) <= operator(peek(stack)))
				tokens[++k] = pop(stack);
			push(stack, tokens[i]);
		}

	}

	// pop all the operators from the stack
	while (!is_empty(stack))
		tokens[++k] = pop(stack);

	// tokens[++k] = '\0';
	printf( "%s", tokens );
}



// main function for testing
int main() {
	FILE *readFile = fopen("tokens.bin", "rb");
    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile) / sizeof(Token);
    fseek(readFile, 0L, SEEK_SET);

    Token* tokens = (Token*)malloc(sizeof(Token)*sz);

    fread(tokens, sizeof(Token), sizeof(tokens), readFile);

    fclose(readFile);

    printf("%ld %c", sz, 10);

    remove("output");

    infix_to_postfix(tokens, 3);

    free(tokens);

    return 0;
	//Token infix = testReadingOfTokens()
	// infix_to_postfix(infix);
}

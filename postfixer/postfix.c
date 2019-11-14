// standard libs
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// local libs
#include "../tokenizer/token.h"
#include "../tokenizer/token_readwrite.h"

// Stack used to store postfix tokenression
struct Stack {
	int top;
	unsigned capacity;
	int* array;
};

// Stack Operations
struct Stack* createStack( unsigned capacity ) {
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
int isEmpty(struct Stack* stack) {
	return stack->top == -1 ;
}

// check item at top of stack
char peek(struct Stack* stack) {
	return stack->array[stack->top];
}

// pop item off top of stack
char pop(struct Stack* stack) {
	if (!isEmpty(stack))
		return stack->array[stack->top--];
	return '$';
}

// push item onto top of stack
void push(struct Stack* stack, char item) {
	stack->array[++stack->top] = item;
}


// check if the given character is operand
int isOperand(Token token) {
	if (token.tokenType == OPERATOR){
		return 1;
	}
	return 0;
}

// returns importance of a given operator
int Prec(Token token) {
	switch (token.val) {
		case '+':
		case '-':
			return 1;

		case '*':
		case '/':
			return 2;

		case '^':
			return 3;
	}
	return -1;
}


// converts infix to postfix
int infixToPostfix(Token* tokens) {
	int i, k;

	// creates a stack of capacity equal to tokenression size
	struct Stack* stack = createStack(strlen(tokens));
	if(!stack)
		return -1 ;

	for (i = 0, k = -1; tokens[i]; ++i) {
		// if the character is an operand, add it to output.
		if (isOperand(tokens[i]))
			tokens[++k] = tokens[i];

		// if the character is an ‘(‘, push it to the stack.
		else if (tokens[i] == '(')
			push(stack, tokens[i]);

		// if the character is an ‘)’, pop and output from the stack
		// until an ‘(‘ is encountered.
		else if (tokens[i] == ')') {
			while (!isEmpty(stack) && peek(stack) != '(')
				tokens[++k] = pop(stack);
			if (!isEmpty(stack) && peek(stack) != '(')
				return -1;
			else
				pop(stack);
		}
		else {
			while (!isEmpty(stack) && Prec(tokens[i]) <= Prec(peek(stack)))
				tokens[++k] = pop(stack);
			push(stack, tokens[i]);
		}

	}

	// pop all the operators from the stack
	while (!isEmpty(stack))
		tokens[++k] = pop(stack);

	tokens[++k] = '\0';
	printf( "%s", tokens );
}

// main function for testing
int main() {
	testReadingOfTokens()
	//Token infix = testReadingOfTokens()
	// infixToPostfix(infix);
	return 0;
}

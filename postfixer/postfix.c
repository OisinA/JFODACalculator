// Infix to Postfix converter
// Author: Michael Forde
// Student Number: 117392626
// Extra: DSS, I have a spelling and grammer waver

#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>
// local libs
#include "../tokenizer/token.h"
#include "../tokenizer/token_readwrite.h"


// A structure to represent a stack 
struct StackNode { 
    Token token; 
    struct StackNode* next; 
};

// null token to be outputed if no items in stack
Token null_token;

// node for stack
struct StackNode* new_node(Token token) 
{ 
    struct StackNode* stack_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    stack_node->token = token;
    stack_node->next = NULL;
    return stack_node;
} 

// check if stack is empty
int is_empty(struct StackNode* root) 
{ 
    return !root; 
} 
  
// pushes an item to the stack
void push(struct StackNode** root, Token token) 
{ 
    struct StackNode* stack_node = new_node(token); 
    stack_node->next = *root; 
    *root = stack_node;
} 
  
// pops an iem from the top of the stack
Token pop(struct StackNode** root) 
{ 
    if (is_empty(*root))
        return null_token; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    Token popped = temp->token; 
    free(temp); 
  
    return popped;
}

// also you check the item in the top of the list
Token peek(struct StackNode* root) 
{ 
    if (is_empty(root))
        return null_token;
    return root->token; 
} 


// check if the given token is operand
int is_operand(Token token) {

	if (token.tokenType == INTEGER || token.tokenType == FLOAT){
		return 1;
	}
	return 0;
}

// check if the given token is a operator
int is_operator(Token token) {

	if (token.tokenType == OPERATOR) {
		return 1;
	}
	return 0;
}


// returns importance of a given operator
int operator(Token token) {

	if (token.val == "+" || token.val == "-") {
		return 1;
	}
	if (token.val == "*" || token.val == "/") {
		return 2;
	}

	return -1;
}


// converts postfix tokens from an array of infix tokens
int infix_to_postfix(Token* tokens, int size) {
	// initializing some variables
	int i, k;
	Token x;

	// creates a stack
	struct StackNode* stack = NULL;

	// loop through all the tokens individually
	for (i = 0, k = -1; i < size; ++i) {

		// if the token is an operand, add it to output.
		if (is_operand(tokens[i])) {
			tokens[++k] = tokens[i];
		}

		// if the token is an ‘(‘, push it to the stack.
		else if (tokens[i].tokenType == LPAREN) {
			push(&stack, tokens[i]);
		}

		// if the token is an operator pop the stack until 
		else if (is_operator(tokens[i])) {
			x = pop(&stack);
			while (is_operator(x) && operator(x) >= operator(tokens[i])) {
				tokens[++k] = x;
				x = pop(&stack);
			}
			push(&stack, x);
			push(&stack, tokens[i]);
		}

		// if the token is an ‘)’, pop and output from the stack
		// until an ‘(‘ is encountered.
		else if (tokens[i].tokenType == RPAREN) {
			x = pop(&stack);
			while (x.tokenType != LPAREN) {
				tokens[++k] = x;
				x = pop(&stack);
			}
		}
		else {
			return -1;
		}

	}

	// pop all the operators from the stackW
	while (!is_empty(stack)) {
		x = pop(&stack);
		tokens[++k] = x;
	}

	// write the output to a file
	writeTokensToFile(tokens, size);

	// prints outputted tokens for debugging
	for (int j = 0; j < size; j++) {
      Token token = tokens[j];
      printf("\n### OUPUT VAL ###: VAL: %s TOKEN TYPE: %d\n", token.val, token.tokenType);
    }
}

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

Token null_token;

struct StackNode* new_node(Token token) 
{ 
    struct StackNode* stack_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    stack_node->token = token;
    stack_node->next = NULL;
    return stack_node;
} 

int is_empty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, Token token) 
{ 
    struct StackNode* stack_node = new_node(token); 
    stack_node->next = *root; 
    *root = stack_node;
} 
  
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

Token peek(struct StackNode* root) 
{ 
    if (is_empty(root))
        return null_token;
    return root->token; 
} 


// check if the given character is operand
int is_operand(Token token) {

	if (token.tokenType == INTEGER || token.tokenType == FLOAT){
		return 1;
	}
	return 0;
}


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


// converts infix to postfix
int infix_to_postfix(Token* tokens, int size) {
	int i, k;

	Token x;

	// creates a stack
	struct StackNode* stack = NULL;

	for (i = 0, k = -1; i < size; ++i) {

		// if the token is an operand, add it to output.
		if (is_operand(tokens[i])) {
			tokens[++k] = tokens[i];
		}

		// if the token is an ‘(‘, push it to the stack.
		else if (tokens[i].tokenType == LPAREN) {
			push(&stack, tokens[i]);
		}

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

	writeTokensToFile(tokens, size);

	for (int j = 0; j < size; j++) {
      Token token = tokens[j];
      printf("\n### OUPUT VAL ###: VAL: %s TOKEN TYPE: %d\n", token.val, token.tokenType);
    }
}


// main function for testing
int main() {
    FILE *readFile = fopen("tokens.bin", "rb");
    fseek(readFile, 0L, SEEK_END);
    int sz = ftell(readFile) / sizeof(Token);
    rewind(readFile);
    Token* tokens = (Token*)malloc(sizeof(Token)*sz);
    fread(tokens, sizeof(Token), sizeof(tokens), readFile);
    fclose(readFile);
    infix_to_postfix(tokens, sz);
    free(tokens);

    return 0;
}

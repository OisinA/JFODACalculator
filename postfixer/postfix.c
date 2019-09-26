#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 


// Stack used to store postfix expression
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
int isOperand(char c) { 
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); 
} 

// returns importance of a given operator
int Prec(char ch) { 
	switch (ch) { 
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
int infixToPostfix(char* exp) { 
	int i, k; 

	// creates a stack of capacity equal to expression size 
	struct Stack* stack = createStack(strlen(exp)); 
	if(!stack)
		return -1 ; 

	for (i = 0, k = -1; exp[i]; ++i) { 
		// if the character is an operand, add it to output. 
		if (isOperand(exp[i])) 
			exp[++k] = exp[i]; 
		
		// if the character is an ‘(‘, push it to the stack. 
		else if (exp[i] == '(') 
			push(stack, exp[i]); 
		
		// if the character is an ‘)’, pop and output from the stack 
		// until an ‘(‘ is encountered. 
		else if (exp[i] == ')') { 
			while (!isEmpty(stack) && peek(stack) != '(') 
				exp[++k] = pop(stack); 
			if (!isEmpty(stack) && peek(stack) != '(') 
				return -1;	 
			else
				pop(stack); 
		}
		else { 
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack))) 
				exp[++k] = pop(stack); 
			push(stack, exp[i]); 
		}

	}

	// pop all the operators from the stack 
	while (!isEmpty(stack)) 
		exp[++k] = pop(stack ); 

	exp[++k] = '\0'; 
	printf( "%s", exp ); 
} 

// main function for testing
int main() { 
	char exp[] = "5*(a-c)+3"; 
	infixToPostfix(exp); 
	return 0; 
} 

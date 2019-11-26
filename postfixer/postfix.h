#ifndef __POSTFIX__
#define __POSTFIX__

// A structure to represent a stack
struct StackNode {
    Token token;
    struct StackNode* next;
};

struct StackNode* new_node(Token token);
int is_empty(struct StackNode* root);
void push(struct StackNode** root, Token token);
Token pop(struct StackNode** root);
Token peek(struct StackNode* root);
int is_operand(Token token);
int is_operator(Token token);
int operator(Token token);
int infix_to_postfix(Token* tokens, int size);
#endif

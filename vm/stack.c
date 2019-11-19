#include "stack.h"

// Create a stack node with given data
StackNode* newStack(Data data) {
  StackNode* stack = (StackNode*)malloc(sizeof(StackNode));
  stack->data = data;
  stack->next = NULL;
  return stack;
}

// Tests if stack is empty
int isEmpty(StackNode* stack) { return !stack; }

// Returns item in top of stack
Data top(StackNode* stack) { return stack->data; }

// Adds data to top of stack
void push(StackNode** stack, Data data) {
  StackNode* newTop = newStack(data);
  newTop->next = *stack;
  *stack = newTop;
}

// Pop data from top of stack
Data pop(StackNode** stack) {
  if (isEmpty(*stack)) {
    Data data = {-1, 0};
    return data;
  }
  StackNode* temp = *stack;
  *stack = (*stack)->next;
  Data popped = temp->data;
  free(temp);
  return popped;
}

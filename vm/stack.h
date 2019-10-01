#ifndef __VM_STACK__
#define __VM_STACK__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char type;
  long value;
} Data;

typedef struct StackNode StackNode;

struct StackNode {
  Data data;
  StackNode* next;
};

StackNode* newStack(Data data) {
  StackNode* stack = (StackNode*)malloc(sizeof(StackNode));
  stack->data = data;
  stack->next = NULL;
  return stack;
}

int isEmpty(StackNode* stack) { return !stack; }

Data top(StackNode* stack) { return stack->data; }

void push(StackNode** stack, Data data) {
  StackNode* newTop = newStack(data);
  newTop->next = *stack;
  *stack = newTop;
}

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
#endif

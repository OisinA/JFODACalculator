//Header file for the VMs stack
//Author: Arthan Jansen

#ifndef __VM_STACK__
#define __VM_STACK__
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char type;
  int value;
} Data;

typedef struct StackNode StackNode;

struct StackNode {
  Data data;
  StackNode* next;
};

StackNode* newStack(Data data);
int isEmpty(StackNode* stack);
Data top(StackNode* stack);
void push(StackNode** stack, Data data);
Data pop(StackNode** stack);
#endif

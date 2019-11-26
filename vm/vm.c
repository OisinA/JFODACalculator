//VM functions
//Author: Arthan Jansen

#include <math.h>
#include <stdio.h>
#include "../isa/isa.h"
#include "stack.h"
#include "vm.h"

// Executes the given instructions in a stack based Virtual Machine. Returns the Data struct of the final result
Data executeInstructions(char instructions[], int size);
#define OPERATE(x, y, z, op)\
  ({switch (op) {\
  case ADD:\
    z = y + x;\
    break;\
  case SUB:\
    z = y - x;\
    break;\
  case MUL:\
    z = y * x;\
    break;\
  case EXP:\
    z = pow(y, x);\
    break;\
  case DIV:\
    if (x == 0) {\
      printf("Error, divide by 0\n");\
      exit(1);\
    }\
    z = y / x;\
    break;\
  default:\
    printf("Error, unrecognized operator\n");\
    exit(1);\
}})

// Tries to push value from instruction bytes onto the stack
StackNode* pushValue(int type, char* instructions, int size, StackNode* stack) {
  if (size < sizeof(int)) {
    printf("Error, No data after PUSH instruction\n");
    exit(1);
  }
  Data data = {type, *(int*)(instructions)};

  push(&stack, data);
  return stack;
}

// Performs the given operator on the stack
StackNode* operate(int operator, StackNode* stack) {
  if (isEmpty(stack)) {
    printf("Error, Not enough items in stack for operation\n");
    exit(1);
  }
  Data data1 = pop(&stack);
  if (isEmpty(stack)) {
    printf("Error, Not enough items in stack for operation\n");
    exit(1);
  }
  Data data2 = pop(&stack);
  Data data = {data1.type, 0};
  if (data1.type == 0 && data2.type == 0) {
    int value1 = data1.value;
    int value2 = data2.value;
    int result;
    OPERATE(value1, value2, result, operator);
    data.value = result;
  } else {
    float value1;
    float value2;
    float result;
    if (data1.type == 1) {
      value1 = *(float*)&data1.value;
    } else {
      value1 = (float)data1.value;
    }
    if (data2.type == 1) {
      value2 = *(float*)&data2.value;
    } else {
      value2 = (float)data2.value;
    }
    OPERATE(value1, value2, result, operator);
    data.value = *(int*)&result;
    data.type = 1;
  }
  push(&stack, data);
  return stack;
}

// Executes the instructions given and returns the data result
Data executeInstructions(char instructions[], int size) {
  StackNode* stack = NULL;
  for (int i = 0; i < size; i++) {
    switch (instructions[i]) {
      case PUSHINT:
      case PUSHFLOAT:
        stack =
            pushValue(instructions[i], instructions + i + 1,
              (size - (i + 1)) * (sizeof(char)), stack);
        i += sizeof(int);
        break;
      case ADD:
      case SUB:
      case MUL:
      case DIV:
      case EXP:
        stack = operate(instructions[i], stack);
        break;
      default:
        printf("Error, unrecognized instruction %d\n", instructions[i]);
        break;
    }
  }

  Data data = pop(&stack);
  return data;
}

#include <math.h>
#include <stdio.h>
#include "../isa/isa.h"
#include "stack.h"

StackNode* pushValue(int type, char* instructions, int i, int size, StackNode* stack) {
  printf("%d:%d%c", i, size/sizeof(char), 10);
  if (size - (sizeof(char) * (i + 1)) < sizeof(int)) {
    printf("Error, No data after PUSH instruction");
    exit(1);
  }
  printf("Loaded %d", *(int*)(instructions + i + 1));
  Data data = {type, *(int*)(instructions + i + 1)};

  push(&stack, data);
  return stack;
}

StackNode* operate(int operator, StackNode* stack) {
  if (isEmpty(stack)) {
    printf("Error, Not enough items in stack for operation");
    exit(1);
  }
  Data data1 = pop(&stack);
  if (isEmpty(stack)) {
    printf("Error, Not enough items in stack for operation");
    exit(1);
  }
  Data data2 = pop(&stack);
  if (data1.type != data2.type) {
    printf("%d %d%c", data1.type, data2.type, 10);
    printf("Error, cannot operate on Float with int");
    exit(1);
  }
  Data data = {data1.type, 0};
  if (data1.type == 1) {
    data.value = 1;
    data1.value = *(float*)&data1.value;
    data2.value = *(float*)&data2.value;
  }
  switch (operator) {
    case ADD:
      data.value = data1.value + data2.value;
      break;
    case SUB:
      data.value = data1.value - data2.value;
      break;
    case MUL:
      data.value = data1.value * data2.value;
      break;
    case EXP:
      data.value = pow(data1.value, data2.value);
      break;
    case DIV:
      data.value = data1.value / data2.value;
      break;
    default:
      printf("Error, unrecognized instruction");
      exit(1);
  }
  if (data1.type == 1) {
  }
  push(&stack, data);
  return stack;
}

int main(int argc, char* argv[]) {
  FILE* fp = fopen(argv[1], "r");  // Open file name specified in command line
  fseek(fp, 0, SEEK_END);          // Seek to the end of the file
  int size = ftell(fp);  // Store the current location as the size of the file
  char instructions[size];           // Create an array of
                                     // Instructions
  rewind(fp);                        // Rewind to the start of the file
  fread(instructions, size, 1, fp);  // Read the binary from the file
  StackNode* stack = NULL;
  for (int i = 0; i < size; i++) {
    printf("instruction:%x%c", instructions[i], 10);
    switch (instructions[i]) {
      case PUSHINT:
        stack = pushValue(0, instructions, i, sizeof(instructions), stack);
        i += sizeof(int);
        break;
      case PUSHFLOAT:
        stack = pushValue(1, instructions, i, sizeof(instructions), stack);
        i += sizeof(int);
        break;
      default:
        stack = operate(instructions[i], stack);
    }
  }

  Data data = pop(&stack);
  if (data.type == 0) {
    printf("%ld", data.value);
  } else {
    printf("%f", *(float*)&data.value);
  }

  return 0;
}

#include <math.h>
#include <stdio.h>
#include "../isa/isa.h"
#include "stack.h"

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
  if (data1.type != data2.type) {
    printf("Error, cannot operate on Float with int\n");
    exit(1);
  }
  Data data = {data1.type, 0};
  float value1 = 0.0;
  float value2 = 0.0;
  float result = 0.0;
  if (data1.type == 1) {
    value1 = *(float*)&data1.value;
    value2 = *(float*)&data2.value;
    data.value = *(int*)&result;
  } else {
    value1 = (float)data1.value;
    value2 = (float)data2.value;
  }
  switch (operator) {
    case ADD:
      result = value2 + value1;
      break;
    case SUB:
      result = value2 - value1;
      break;
    case MUL:
      result = value2 * value1;
      break;
    case EXP:
      result = pow(value2, value1);
      break;
    case DIV:
      if (value1 == 0) {
        printf("Error, divide by 0");
        exit(1);
      }
      result = value2 / value1;
      break;
    default:
      printf("Error, unrecognized operator\n");
      exit(1);
  }
  data.value = *(int*)&result;
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
    switch (instructions[i]) {
      case PUSHINT:
      case PUSHFLOAT:
        stack =
            pushValue(instructions[i], instructions + i + 1,
                      sizeof(instructions) - (sizeof(char) * (i + 1)), stack);
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
  if (data.type == 0) {
    printf("%ld\n", data.value);
  } else {
    printf("%f\n", *(float*)&data.value);
  }

  return 0;
}

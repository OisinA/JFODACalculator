#include <math.h>
#include <stdio.h>
#include "../isa/isa.h"
#include "stack.h"

struct pushint {
  int data;
};

struct pushfloat {
  float data;
};

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
    Data data = {0, 0};
    Data data1 = {0, 0};
    Data data2 = {0, 0};
    switch (instructions[i]) {
      case PUSHINT:
        if (sizeof(instructions) - (sizeof(char) * (i + 1)) < sizeof(long)) {
          printf("Error, No data after PUSHINT instruction");
          return 1;
        }
        data.value = *(long*)(instructions + i + 1);
        push(&stack, data);
        i += 8;
        break;
      case PUSHFLOAT:
        if (sizeof(instructions) - (sizeof(char) * (i + 1)) < sizeof(long)) {
          printf("Error, No data after PUSHFLOAT instruction");
          return 1;
        }
        printf("%f", (*(float*)(instructions + i + 1)));
        data.value = (*(float*)(instructions + i + 1));
        data.type = 1;
        push(&stack, data);
        i += 8;
        break;
      case ADD:
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for ADD");
          return 1;
        }
        data1 = pop(&stack);
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for ADD");
          return 1;
        }
        data2 = pop(&stack);
        if (data1.type != data2.type) {
          printf("Error, cannot ADD Float with Long");
          return 1;
        }
        if (data1.type == 0) {
          long result = data1.value + data2.value;
          Data data = {0, result};
          push(&stack, data);
        } else {
          float result = (float)(data1.value) + (float)(data2.value);
          Data data = {1, result};
          push(&stack, data);
        }
        break;
      case SUB:
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for SUB");
          return 1;
        }
        data1 = pop(&stack);
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for SUB");
          return 1;
        }
        data2 = pop(&stack);
        if (data1.type != data2.type) {
          printf("Error, cannot SUB Float with Long");
          return 1;
        }
        if (data1.type == 0) {
          long result = data1.value - data2.value;
          Data data = {0, result};
          push(&stack, data);
        } else {
          float result = (float)(data1.value) - (float)(data2.value);
          Data data = {1, result};
          push(&stack, data);
        }
        break;
      case MUL:
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for MUL");
          return 1;
        }
        data1 = pop(&stack);
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for MUL");
          return 1;
        }
        data2 = pop(&stack);
        if (data1.type != data2.type) {
          printf("Error, cannot MUL Float with Long");
          return 1;
        }
        if (data1.type == 0) {
          long result = data1.value * data2.value;
          Data data = {0, result};
          push(&stack, data);
        } else {
          float result = (float)(data1.value) * (float)(data2.value);
          Data data = {1, result};
          push(&stack, data);
        }
        break;
      case DIV:
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for DIV");
          return 1;
        }
        data1 = pop(&stack);
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for DIV");
          return 1;
        }
        data2 = pop(&stack);
        if (data1.type != data2.type) {
          printf("Error, cannot DIV Float with Long");
          return 1;
        }
        if (data1.type == 0) {
          long result = data1.value / data2.value;
          Data data = {0, result};
          push(&stack, data);
        } else {
          float result = (float)(data1.value) / (float)(data2.value);
          Data data = {1, result};
          push(&stack, data);
        }
        break;
      case EXP:
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for EXP");
          return 1;
        }
        data1 = pop(&stack);
        if (isEmpty(stack)) {
          printf("Error, Not enough items in stack for EXP");
          return 1;
        }
        data2 = pop(&stack);
        if (data1.type != data2.type) {
          printf("Error, cannot EXP Float with Long");
          return 1;
        }
        if (data1.type == 0) {
          long result = pow(data1.value, data2.value);
          Data data = {0, result};
          push(&stack, data);
        } else {
          float result = pow((float)(data1.value), (float)(data2.value));
          Data data = {1, result};
          push(&stack, data);
        }
        break;
      default:
        printf("Error, Unrecognized instruction");
        return 1;
    }
  }

  Data data = pop(&stack);
  if (data.type == 0) {
    printf("%ld", data.value);
  } else {
    printf("%f", (float)data.value);
  }

  return 0;
}

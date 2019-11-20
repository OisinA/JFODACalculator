//Tests for the vm
//Author: Arthan Jansen

#include <ctap.h>
#include "vm.h"
#include "../isa/isa.h"
#include "stack.h"
TESTS {
  StackNode* stack = NULL; // Create an empty stack
  int instructionValue = 1; // Create a value to add to the stack
  stack = pushValue(0, (char*)&instructionValue, 4, stack); // Push the value to the stack twice
  stack = pushValue(0, (char*)&instructionValue, 4, stack);
  Data data = top(stack);
  // Ensure correct data is in top of stack
  ok(data.value == 1, "value: %d is not expected 1", data.value);
  ok(data.type == 0, "type: %d is not expected 0", data.type);
  stack = operate(ADD, stack);
  // Ensure stack is not empty after operation
  ok(!isEmpty(stack), "Stack has 1 items");
  // Ensure addition worked correctly
  ok(top(stack).value == 2, "addition %d is not expected 2", top(stack).value);
  pop(&stack);
  // Ensure stack only had 1 item in stack
  ok(isEmpty(stack), "Stack is empty");

  char instructions[] = {
    PUSHINT,
    (char) 2,
    (char) 0,
    (char) 0,
    (char) 0,
    PUSHINT,
    (char) 3,
    (char) 0,
    (char) 0,
    (char) 0,
    PUSHINT,
    (char) 4,
    (char) 0,
    (char) 0,
    (char) 0,
    ADD,
    MUL,
    PUSHINT,
    (char) 1,
    (char) 0,
    (char) 0,
    (char) 0,
    DIV
  };
  Data result = executeInstructions(instructions, sizeof(instructions) / sizeof(char));
  // Ensure correct data is returned
  ok(result.value == 14, "value: %d is not expected 14", result.value);
  ok(result.type == 0, "type: %d is not expected 0", result.type);
}

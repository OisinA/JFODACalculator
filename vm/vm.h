//Header file for vm functions
//Author: Arthan Jansen

#ifndef __VM__
#define __VM__

#include "stack.h"

Data executeInstructions(char instructions[], int size);
StackNode* pushValue(int type, char* instructions, int size, StackNode* stack);
StackNode* operate(int operator, StackNode* stack);

#endif

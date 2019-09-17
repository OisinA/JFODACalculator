#include <stdio.h>
#include "../isa/isa.h"

int main(int argc, char* argv[]) {
  FILE* fp = fopen(argv[1], "r");  // Open file name specified in command line
  fseek(fp, 0, SEEK_END);          // Seek to the end of the file
  int size = ftell(fp);  // Store the current location as the size of the file
  char instructions[size];  // Create an array of
                                                         // Instructions
  rewind(fp);                        // Rewind to the start of the file
  fread(instructions, size, 1, fp);  // Read the binary from the file
  for (int i = 0; i < size; i++) {
      switch(instructions[i]){
          case PUSHINT:
            
            break;
      }
  }

  return 0;
}

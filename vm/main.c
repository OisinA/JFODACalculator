// Main file to read input files and run VM
//Author: Arthan Jansen

#include "vm.h"

// Main file for the VM. Reads in instructions from the output file. Runs instructions on VM.
int main(int argc, char* argv[]) {
  FILE* fp = fopen("output", "r");  // Open file name specified in command line
  fseek(fp, 0, SEEK_END);          // Seek to the end of the file
  int size = ftell(fp); // Store the current location as the size of the file
  char instructions[size];           // Create an array of
                                     // Instructions
  rewind(fp);                        // Rewind to the start of the file
  fread(instructions, size, 1, fp);  // Read the binary from the file
  Data data = executeInstructions(instructions, size);
  if (data.type == 0) {
    printf("%d\n", data.value);
  } else {
    printf("%f\n", *(float*)&data.value);
  }
  return 0;
}

// Main file for file input, plus closing the file
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "token.h"

// Read an input file called test.txt into an array of characters
// whose pointer is returned.
char * readFile() {
  // Create a file pointer
  FILE *fp;

  // Allocate memory for the array of characters.
  char* expr = (char*)malloc(sizeof(char)*255);

  // Open the file called test.txt
  fp = fopen("test.txt" , "r");

  // If the file does not exist, an error should be generated.
  if(fp == NULL) {
    perror("Error: Could not open the file.");
    return NULL;
  }

  // File exists, get the first line
  if( fgets (expr, 100, fp) == NULL ) {
    puts("No numbers found.");
  }

  fclose(fp);

  return expr;
}

// Free the memory associated with the array of chars.
void closeFile(char* fileStr) {
  free(fileStr);
}

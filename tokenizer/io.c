// Main file for file input, plus closing the file
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "token.h"

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
  if( fgets (expr, 60, fp) == NULL ) {
    puts("No numbers found.");
  }

  fclose(fp);

  return expr;
}

void closeFile(char* fileStr) {
  // Free the memory associated with the array of chars
  free(fileStr);
}

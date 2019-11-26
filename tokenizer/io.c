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
  fp = fopen("input.txt" , "r");

  // If the file does not exist, an error should be generated.
  if(fp == NULL) {
    perror("input.txt not found. Creating file input.txt instead...");

    createInputFile();
    fp = fopen("input.txt" , "r");
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

int createInputFile() {
  FILE *fp;
  fp = fopen("input.txt", "w");

  fprintf(fp, "%s", "(1.3 + 4.5 * 7 ) - 2");
  fclose(fp);
  return 0;
}

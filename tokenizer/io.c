#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char * readFile();
void closeFile(char*);

// Read in the file called test.txt and assign
// this to an array of characters, whose pointer is returned.
char * readFile() {
  // Create a file pointer
  FILE *fp;
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
  free(fileStr);
}

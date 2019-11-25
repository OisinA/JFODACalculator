// Header file for file input, plus closing the file.
// Author Name: Silvia O'Dwyer
// Author Student Number: 117333306

#ifndef __IO__
#define __IO__

/*
 * Function:  readFile
 * --------------------
 * Read in the file called test.txt and assign this to an array of characters,
 * whose pointer is returned.
 *
 *  returns: an array of characters which represent the arithmetical expression
 */
char * readFile();

/*
 * Function:  closeFile
 * --------------------
 * Free the memory associated with the array of characters.
 *
 */
void closeFile(char*);

#endif

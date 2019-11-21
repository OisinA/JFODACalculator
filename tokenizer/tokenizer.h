#ifndef __TOKENIZER__
#define __TOKENIZER__

int isoperator(char c);
char* readFile();
void exportToken();
void tokenize(char *expr);

#endif

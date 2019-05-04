#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "str.h"

#define FIVE_ROWS    5
#define FIVE_COLUMNS 5

#define NEWLINE           printf("\n")

extern char droppedLetter;

///MATRIX OPERATIONS///////////////////////////////////////////////////////////////////////////
char**  allocCharMat(int rows, int cols);

void    freeMat(int rows, char **matrix);

void    showMat(int rows, int cols, const char** matrix);

char**  alphabMatGen();

char**  keyMatGen(const char* key);

void    findCharInKeyMat(const char **mat, char charToFind, int* row, int* col);


#endif
#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"


#define MAX_STR 10000
#define LOWER_UPPERCASE_OFFSET 32
#define NB_LETTERS        26
#define FIVE_ROWS    5
#define FIVE_COLUMNS 5
#define PLAYFAIR_SIZE     25
#define BIGRAPH_SIZE      2
#define NEWLINE           printf("\n")

///MATRIX OPERATIONS///////////////////////////////////////////////////////////////////////////
char** allocCharMat(int rows, int cols);

void   freeMat(int rows, char **matrix);

void   showMat(int rows, int cols, const char** matrix);

char** alphabMatGen(char exceptC);

char** keyMatGen(const char* key, char exceptC);

void findCharInMat(const char **mat, char charToFind, int* row, int* col);


#endif
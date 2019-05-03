#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

#define MAX_STR 10000
#define LOWER_UPPERCASE_OFFSET 32
#define NB_LETTERS        26
#define PLAYFAIR_R_C_SIZE 5
#define PLAYFAIR_SIZE     25
#define BIGRAPH_SIZE      2

///Basic functions//////////////////////////////////////////////////////////////////
int* alter_tab_sign(int n, const int* tab);

char upperC(char c);
char lowerC(char c);

char* upperStr(char* strIn);

void cpy_int_tab(int n, int* tab_d, int* tab_s);

unsigned char shiftLetter(const char original_letter, int shift_amount);

///////////////////////////////////////////////////////////////////////////////////
int char_to_int(char letter);

int* str_to_int(const char* key);

char* int_to_str(int nb, const int* tab);

///Find Char//////////////////////////////////////////////////////////////////////
bool char_in_str(char c, char* s);

bool char_in_alphabets(char c);

/////////////////////////////////////////////////////////////////////////////////////
char* removeDuplicates(const char* strIn);

////////////////////////////////////////////////////////////////////////////////////////
int* randIntKey(unsigned int keyLength);

#endif
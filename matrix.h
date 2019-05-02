#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

#define MAX_STR 10000
#define LOWER_UPPERCASE_OFFSET 32
#define NB_LETTERS        26
#define PLAYFAIR_R_C_SIZE 5
#define PLAYFAIR_SIZE     25
#define BIGRAPH_SIZE      2
#define NEWLINE           printf("\n")

///MATRIX OPERATIONS///////////////////////////////////////////////////////////////////////////
void alphabet_matrix_generator(char alphabet_matrix[][PLAYFAIR_R_C_SIZE], char except_c);

void matrix_key_generator(const char* key, char key_matrix[][PLAYFAIR_R_C_SIZE], char except_c);

void char_matrix_coordinates(const char playfair_key[][PLAYFAIR_R_C_SIZE], const char c_to_find, int* c_coordinates);

void show_matrix(const char matrix[][PLAYFAIR_R_C_SIZE]);

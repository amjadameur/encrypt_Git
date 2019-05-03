#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 10000
#define LOWER_UPPERCASE_OFFSET 32
#define NB_LETTERS        26
#define PLAYFAIR_R_C_SIZE 5
#define PLAYFAIR_SIZE     25
#define BIGRAPH_SIZE      2

///Basic functions//////////////////////////////////////////////////////////////////
int* alter_tab_sign(int n, const int* tab);

int next_char(int index, char* s);

char char_lower_to_uppercase(char c);

void lower_to_uppercase(char* s);

void cpy_int_tab(int n, int* tab_d, int* tab_s);

unsigned char shiftLetter(const char original_letter, int shift_amount);

///////////////////////////////////////////////////////////////////////////////////
int char_to_int(char letter);

int* str_to_int(const char* key);

char* int_to_str(int nb, const int* tab);

///Find Char//////////////////////////////////////////////////////////////////////
int char_in_str(char c, char* s);

int char_in_alphabets(char c);

/////////////////////////////////////////////////////////////////////////////////////
void remove_duplicates(const char* key_i, char* key_o);

char pick_from_alphabets(char* offset, char* s, char except_c);

void fill_blank_space(int start_index, int stop_index, char* processed_text);

////////////////////////////////////////////////////////////////////////////////////////
int* randIntKey(unsigned int keyLength);

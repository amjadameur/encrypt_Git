#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "matrix.h"

#define MAX_STR 10000
#define LOWER_UPPERCASE_OFFSET 32
#define NB_LETTERS        26
#define PLAYFAIR_R_C_SIZE 5
#define PLAYFAIR_SIZE     25
#define BIGRAPH_SIZE      2
#define ENCRYPTION        1
#define DECRYPTION        2


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void caesar_cipher(int key, const char* original_text_i, char* processed_text);

void vigenere_cipher(int key_length, const int* key_i, const char* original_text_i, char* processed_text);

void generate_one_time_pad_key(unsigned int original_text_length, int* one_time_pad_key);
void one_time_pad_cipher(unsigned int original_text_length, const int* one_time_pad_key_i, const char* original_text_i, char* processed_text);

void encrypt_playfair_bigraph(int encrypt_decrypt, char playfair_key[][PLAYFAIR_R_C_SIZE], int* bigraph_coordinates_c1, int* bigraph_coordinates_c2, char* encr_c1, char* encr_c2);
void playfair_cipher(int encrypt_decrypt, const char* key, const char* original_text, char* processed_text);

void four_square_encrypt_bigraph(int encrypt_decrypt, char alphabet_matrix[][PLAYFAIR_R_C_SIZE], char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2);
void four_square_cipher(int encrypt_decrypt, const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c);

void two_square_encrypt_bigraph(char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2);
void two_square_cipher(const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c);

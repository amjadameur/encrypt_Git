#ifndef ENCRYPTION_H
#define ENCRYPTION_H

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
char* caesar(int key, const char* plainText);
char* caesarEncr(int key, const char* plainText);
char* caesarDecr(int key, const char* cipheredText);

char* vigenere(unsigned int keyLength, const int* key, const char* plainText);
char* vigenereEncr(const char* key, const char* plainText);
char* vigenereDecr(const char* key, const char* cipheredText);

char* oneTimePad(const int* key, const char* plainText);
char* oneTimePadEncr(int** key, const char* plainText);
char* oneTimePadDecr(const int* key, const char* cipheredText);

void  playfairBigraphEncr(int encryptDecrypt, char** keyMat, char* c1, char* c2);
char* playfairCipher(int encryptDecrypt, const char* key, const char* plainText);
char* playfairEncr(const char* key, const char* plainText);
char* playfairDecr(const char* key, const char* cipheredText);

/*
void four_square_encrypt_bigraph(int encrypt_decrypt, char alphabet_matrix[][PLAYFAIR_R_C_SIZE], char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2);
void four_square_cipher(int encrypt_decrypt, const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c);

void two_square_encrypt_bigraph(char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2);
void two_square_cipher(const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c);
*/
#endif
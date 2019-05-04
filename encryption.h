#ifndef __ENCRYPTION_H__
#define __ENCRYPTION_H__

#include "matrix.h"

#define ENCRYPTION        1
#define DECRYPTION        2

typedef struct twoKeys {
	char** keyMat1;
	char** keyMat2;
} key2Matrices;

typedef struct threeKeys {
	char** alphabMat;
	char** keyMat1;
	char** keyMat2;
} key3Matrices;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char*   caesar(int key, const char* plainText);
char*   caesarEncr(int key, const char* plainText);
char*   caesarDecr(int key, const char* cipheredText);

char*   vigenere(unsigned int keyLength, const int* key, const char* plainText);
char*   vigenereEncr(const char* key, const char* plainText);
char*   vigenereDecr(const char* key, const char* cipheredText);

char*   oneTimePad(const int* key, const char* plainText);
char*   oneTimePadEncr(int** key, const char* plainText);
char*   oneTimePadDecr(const int* key, const char* cipheredText);

void    playfairDigraphEncr(int encryptDecrypt, char** keyMat, char* c1, char* c2);
char*   playfair(int encryptDecrypt, const char* key, const char* plainText);
char*   playfairEncr(const char* key, const char* plainText);
char*   playfairDecr(const char* key, const char* cipheredText);

void    fourSquareDigraphEncr(key3Matrices keys, char *c1, char *c2);
void    fourSquareDigraphDecr(key3Matrices keys, char *c1, char *c2);
char*   fourSquare(int encryptDecrypt, const char* key1, const char* key2, const char* plainText);	
char*   fourSquareEncr(const char* key1, const char* key2, const char* plainText);	
char*   fourSquareDecr(const char* key1, const char* key2, const char* cipheredText);	

// Ici on utilise la version verticale de cette méthode de cryptage
void    twoSquareDigraphEncr(key2Matrices keys, char *c1, char *c2);
char*   twoSquare(const char* key1, const char* key2, const char* plainText);	
char*   twoSquareEncr(const char* key1, const char* key2, const char* plainText);	
char*   twoSquareDecr(const char* key1, const char* key2, const char* cipheredText);	

#endif
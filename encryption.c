#include "encryption.h"

//CAESAR CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
char* caesar(int key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char* cipheredText = (char*) malloc((textLength+1)*sizeof(char));
	char plainLetter;
	unsigned char cipheredLetter;

	for (int i = 0; plainText[i] != '\0'; i++)
	{
		plainLetter = plainText[i];
		cipheredLetter = shiftLetter(plainLetter, key);
		cipheredText[i] = cipheredLetter;
	}
	return cipheredText;
}

char* caesarEncr(int key, const char* plainText) {
	return caesar(key, plainText);
}

char* caesarDecr(int key, const char* cipheredText) {
	return caesar(-key, cipheredText);
}


//VIGENERE CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
char* vigenere(unsigned int keyLength, const int* Key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char* cipheredText = (char*) malloc((textLength+1)*sizeof(char));
	char plainLetter;
	unsigned char cipheredLetter;
	int shiftAmount;

	for (int i = 0; i<textLength; i+=keyLength) {
		for (int j = 0; j<keyLength; j++) {
			if (plainText[i+j] == '\0') {
				break;
			} else {
				plainLetter = plainText[i+j];
				shiftAmount = Key[j];
				cipheredLetter = shiftLetter(plainLetter, shiftAmount);
				cipheredText[i+j] = cipheredLetter;
			}
		}	
	}
	return cipheredText;
}

char* vigenereEncr(const char* key, const char* plainText) {
	int* intKey = str_to_int(key);
	unsigned int keyLength = strlen(key);
	return vigenere(keyLength, intKey, plainText);
}

char* vigenereDecr(const char* key, const char* cipheredText) {
	unsigned int keyLength = strlen(key);
	int *p, *intKey;
	intKey = str_to_int(key);
	p      = intKey;
	intKey = alter_tab_sign(keyLength, intKey);
	free(p); // clearing the allocated are allocated by str_to_int
	return vigenere(keyLength, intKey, cipheredText);
}


//ONE TIME PAD CIPHER///////////////////////////////////////////////////////////////////////////////////////////////


char* oneTimePad(const int* key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	int shiftAmount;
	char plainLetter, cipheredLetter;
	char* cipheredText = (char*) malloc((textLength+1)*sizeof(char));

	for (int i = 0; i < textLength; ++i)
	{
		shiftAmount = key[i];
		plainLetter = plainText[i];
		cipheredLetter = shiftLetter(plainLetter, shiftAmount);
		cipheredText[i] = cipheredLetter;
	}	
	return cipheredText;
}

char* oneTimePadEncr(int** key, const char* plainText) {
	// the key has the same length as the plainText
	unsigned int keyLength = strlen(plainText);
	*key = randIntKey(keyLength);
	return oneTimePad(*key, plainText);
}

char* oneTimePadDecr(const int* key, const char* cipheredText) {
	// the key has the same length as the plainText
	unsigned int keyLength = strlen(cipheredText);
	int* decrKey = alter_tab_sign(keyLength, key);
	char* plainText =  oneTimePad(decrKey, plainText);
	free(decrKey);
	return plainText;
}


//PLAYFAIR CIPHER///////////////////////////////////////////////////////////////////////////////////////////////

void playfairBigraphEncr(int encryptDecrypt, char** keyMat, char* c1, char* c2) {
	// upperCase
	*c1 = upperC(*c1);
	*c2 = upperC(*c2);
	
	// coordinates of the c1 and c2 in the matrix
	int c1_r, c1_c, c2_r, c2_c;
	findCharInMat(keyMat, *c1, &c1_r, &c1_c);
	findCharInMat(keyMat, *c2, &c2_r, &c2_c);

	if (c1_r == c2_r) {
		if (c1_c == FIVE_COLUMNS-1 || encryptDecrypt == DECRYPTION) {
			*c1 = keyMat[c1_r][c1_c-1];
		} else {
			*c1 = keyMat[c1_r][c1_c+1];
		}

		if (c2_c == FIVE_COLUMNS-1 || encryptDecrypt == DECRYPTION) {
			*c2 = keyMat[c2_r][c2_c-1];
		} else {
			*c2 = keyMat[c2_r][c2_c+1];
		}
	}

	else if (c1_c == c2_c) {
		if (c1_r == FIVE_ROWS-1 || encryptDecrypt == DECRYPTION) {
			*c1 = keyMat[c1_r-1][c1_c];
		} else {
			*c1 = keyMat[c1_r+1][c1_c];
		}

		if (c2_r == FIVE_ROWS-1 || encryptDecrypt == DECRYPTION) {
			*c2 = keyMat[c2_r-1][c2_c];
		} else {
			*c2 = keyMat[c2_r+1][c2_c];
		}

	} else {
		*c1 = keyMat[c1_r][c2_c];
		*c2 = keyMat[c2_r][c1_c];
	}
}

char* playfairCipher(int encryptDecrypt, const char* key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char *cipheredText = (char*) malloc((textLength+1)*sizeof(char));
	char **keyMat = keyMatGen(key, 'q');
	char c1 = '0', c2 = '0'; 
	int i = 0, j = 0;

	while(i<textLength) {
		c1 = plainText[i];
		if (!char_in_alphabets(c1)) {
			cipheredText[i++] = c1;
		} else {
			j = i++; // j stocke l'indice de c1
			while(!char_in_alphabets(c2 = plainText[i])) cipheredText[i++] = c2;
			playfairBigraphEncr(encryptDecrypt, keyMat, &c1, &c2);
			cipheredText[j] = c1;
			cipheredText[i++] = c2;
		}
	}
	free(keyMat);
	return cipheredText;	
}

char* playfairEncr(const char* key, const char* plainText) {
	return playfairCipher(ENCRYPTION, key, plainText);
}

char* playfairDecr(const char* key, const char* cipheredText) {
	return playfairCipher(DECRYPTION, key, cipheredText);
}


/*
//FOUR SQUARE CIPHER////////////////////////////////////////////////////////////////////////////////////////////////
void four_square_encrypt_bigraph(int encrypt_decrypt, char alphabet_matrix[][PLAYFAIR_R_C_SIZE], char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2) {	
	int bigraph_coordinates_c1[BIGRAPH_SIZE];
	int bigraph_coordinates_c2[BIGRAPH_SIZE];
	int c1_r, c1_c, c2_r, c2_c;

	if (encrypt_decrypt == ENCRYPTION)
	{
		char_matrix_coordinates(alphabet_matrix, *c1, bigraph_coordinates_c1);
		char_matrix_coordinates(alphabet_matrix, *c2, bigraph_coordinates_c2);
	} else {
		char_matrix_coordinates(key1, *c1, bigraph_coordinates_c1);
		char_matrix_coordinates(key2, *c2, bigraph_coordinates_c2);		
	}
	c1_r = bigraph_coordinates_c1[0];
	c1_c = bigraph_coordinates_c1[1];
	c2_r = bigraph_coordinates_c2[0];
	c2_c = bigraph_coordinates_c2[1];	

	*c1 = alphabet_matrix[c1_r][c2_c];
	*c2 = alphabet_matrix[c2_r][c1_c];
}

void four_square_cipher(int encrypt_decrypt, const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c) {
	char alphabet_matrix[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];	
	char key1[strlen(key1_i)];
	char key2[strlen(key2_i)];
	char four_square_key1[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];
	char four_square_key2[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];
	unsigned int original_text_length = strlen(original_text_i);
	char original_text[MAX_STR];
	char c1, c2;
	int c2_index, i = 0;

    // pre-treatment
	alphabet_matrix_generator(alphabet_matrix, except_c);	
	strcpy(key1, key1_i);
	strcpy(key2, key2_i);
	strcpy(original_text, original_text_i);
	matrix_key_generator(key1, four_square_key1, except_c);
	matrix_key_generator(key2, four_square_key2, except_c);
	lower_to_uppercase(original_text);

	while(i<original_text_length) {
		c1 = original_text[i];
		c2_index = next_char(i, original_text);
		if(!char_in_alphabets(c1) || !c2_index) {
			processed_text[i] = original_text[i];
			i++;
		} else {
			c2 = original_text[c2_index];
			four_square_encrypt_bigraph(encrypt_decrypt , alphabet_matrix, four_square_key1, four_square_key2, &c1, &c2);	
			fill_blank_space(i+1, c2_index-1, processed_text);
			processed_text[c2_index] = c2;
			processed_text[i]        = c1;
			i = c2_index+1;
		}
	}
}

//TWO SQUARES////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void two_square_encrypt_bigraph(char key1[][PLAYFAIR_R_C_SIZE], char key2[][PLAYFAIR_R_C_SIZE], char* c1, char* c2) {	
	int bigraph_coordinates_c1[BIGRAPH_SIZE];
	int bigraph_coordinates_c2[BIGRAPH_SIZE];
	int c1_r, c1_c, c2_r, c2_c;

	char_matrix_coordinates(key1, *c1, bigraph_coordinates_c1);
	char_matrix_coordinates(key2, *c2, bigraph_coordinates_c2);		
	c1_r = bigraph_coordinates_c1[0];
	c1_c = bigraph_coordinates_c1[1];
	c2_r = bigraph_coordinates_c2[0];
	c2_c = bigraph_coordinates_c2[1];	

	*c1 = key1[c1_r][c2_c];
	*c2 = key2[c2_r][c1_c];
}


void two_square_cipher(const char* key1_i, const char* key2_i, const char* original_text_i, char* processed_text, char except_c) {
	char key1[strlen(key1_i)];
	char key2[strlen(key2_i)];
	char two_square_key1[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];
	char two_square_key2[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];
	unsigned int original_text_length = strlen(original_text_i);
	char original_text[MAX_STR];
	char c1, c2;
	int c2_index, i = 0;

    // pre-treatment
	strcpy(key1, key1_i);
	strcpy(key2, key2_i);
	strcpy(original_text, original_text_i);
	matrix_key_generator(key1, two_square_key1, except_c);
	matrix_key_generator(key2, two_square_key2, except_c);
	lower_to_uppercase(original_text);

	while(i<original_text_length) {
		c1 = original_text[i];
		c2_index = next_char(i, original_text);
		if(!char_in_alphabets(c1) || !c2_index) {
			processed_text[i] = original_text[i];
			i++;
		} else {
			c2 = original_text[c2_index];
			two_square_encrypt_bigraph(two_square_key1, two_square_key2, &c1, &c2);	
			fill_blank_space(i+1, c2_index-1, processed_text);
			processed_text[c2_index] = c2;
			processed_text[i]        = c1;
			i = c2_index+1;
		}
	}
}
*/
#include "encryption.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
char* caesar(int key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char* cipheredText = (char*) malloc((textLength+1)*sizeof(char));
	char plainLetter;
	unsigned char cipheredLetter;

	for (int i = 0; plainText[i] != '\0'; i++)
	{
		plainLetter = plainText[i];
		cipheredLetter  = shiftLetter(key, plainLetter);
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


//////////////////////////////////////////////////////////////////////////////////////////////////////
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
				cipheredLetter = shiftLetter(shiftAmount, plainLetter);
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


//////////////////////////////////////////////////////////////////////////////////////////////////////
char* oneTimePad(const int* key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	int shiftAmount;
	char plainLetter, cipheredLetter;
	char* cipheredText = (char*) malloc((textLength+1)*sizeof(char));

	for (int i = 0; i < textLength; ++i)
	{
		shiftAmount = key[i];
		plainLetter = plainText[i];
		cipheredLetter = shiftLetter(shiftAmount, plainLetter);
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


//////////////////////////////////////////////////////////////////////////////////////////////////////
void playfairDigraphEncr(int encryptDecrypt, char** keyMat, char* c1, char* c2) {
	// coordinates of the c1 and c2 in the matrix
	int c1_r, c1_c, c2_r, c2_c;
	findCharInKeyMat(keyMat, *c1, &c1_r, &c1_c);
	findCharInKeyMat(keyMat, *c2, &c2_r, &c2_c);

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

char* playfair(int encryptDecrypt, const char* key, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char *cipheredText = (char*) malloc((textLength+1)*sizeof(char));
	char **keyMat = keyMatGen(key);
	char c1 = '0', c2 = '0'; 
	int i = 0, j = 0;

	while(i<textLength) {
		c1 = plainText[i];
		if (!isAlphabet(c1)) {
			cipheredText[i++] = c1;
		} else {
			j = i++; // j stocke l'indice de c1
			while(!isAlphabet(c2 = plainText[i])) cipheredText[i++] = c2;
			playfairDigraphEncr(encryptDecrypt, keyMat, &c1, &c2);
			cipheredText[j] = c1;
			cipheredText[i++] = c2;
		}
	}
	free(keyMat);
	return cipheredText;	
}

char* playfairEncr(const char* key, const char* plainText) {
	return playfair(ENCRYPTION, key, plainText);
}

char* playfairDecr(const char* key, const char* cipheredText) {
	return playfair(DECRYPTION, key, cipheredText);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void fourSquareDigraphEncr(key3Matrices keys, char *c1, char *c2) {
	int c1_r, c1_c, c2_r, c2_c;
	findCharInKeyMat(keys.alphabMat, *c1, &c1_r, &c1_c);
	findCharInKeyMat(keys.alphabMat, *c2, &c2_r, &c2_c);	

	*c1 = keys.keyMat1[c1_r][c2_c];
	*c2 = keys.keyMat2[c2_r][c1_c];
}

void fourSquareDigraphDecr(key3Matrices keys, char *c1, char *c2) {
	int c1_r, c1_c, c2_r, c2_c;
	findCharInKeyMat(keys.keyMat1, *c1, &c1_r, &c1_c);
	findCharInKeyMat(keys.keyMat2, *c2, &c2_r, &c2_c);	

	*c1 = keys.alphabMat[c1_r][c2_c];
	*c2 = keys.alphabMat[c2_r][c1_c];
}

char* fourSquare(int encryptDecrypt, const char* key1, const char* key2, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char *cipheredText      = (char*) malloc((textLength+1)*sizeof(char));

	char **alphabMat  = alphabMatGen(key1);
	char **keyMat1    = keyMatGen(key1);
	char **keyMat2    = keyMatGen(key2);
	key3Matrices keys  = {alphabMat, keyMat1, keyMat2};

	char c1 = '0', c2 = '0'; 
	int i = 0, j = 0;

	while(i<textLength) {
		c1 = plainText[i];
		if (!isAlphabet(c1)) {
			cipheredText[i++] = c1;
		} else {
			j = i++; // j stocke l'indice de c1
			while(!isAlphabet(c2 = plainText[i])) cipheredText[i++] = c2;

			if (encryptDecrypt == ENCRYPTION) {
				fourSquareDigraphEncr(keys, &c1, &c2);	
			} else {
				fourSquareDigraphDecr(keys, &c1, &c2);	
			}

			cipheredText[j]   = c1;
			cipheredText[i++] = c2;
		}
	}
	free(keyMat1);
	free(keyMat2);
	free(alphabMat);
	return cipheredText;	
}

char* fourSquareEncr(const char* key1, const char* key2, const char* plainText) {
	return fourSquare(ENCRYPTION, key1, key2, plainText);
}

char* fourSquareDecr(const char* key1, const char* key2, const char* cipheredText) {
	return fourSquare(DECRYPTION, key1, key2, cipheredText);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void  twoSquareDigraphEncr(key2Matrices keys, char *c1, char *c2) {
	int c1_r, c1_c, c2_r, c2_c;
	findCharInKeyMat(keys.keyMat1, *c1, &c1_r, &c1_c);
	findCharInKeyMat(keys.keyMat2, *c2, &c2_r, &c2_c);
	
	// Ici on utilise la version verticale de cette méthode du cryptage
	if(c1_c != c2_c) {		
		*c1 = keys.keyMat1[c1_r][c2_c];
		*c2 = keys.keyMat2[c2_r][c1_c];			
	} else {
		*c1 = upperC(*c1);
		*c2 = upperC(*c2);
	}
}

char* twoSquare(const char* key1, const char* key2, const char* plainText) {
	unsigned int textLength = strlen(plainText);
	char *cipheredText      = (char*) malloc((textLength+1)*sizeof(char));

	char **keyMat1     = keyMatGen(key1);
	char **keyMat2     = keyMatGen(key2);
	key2Matrices keys  = {keyMat1, keyMat2};

	showMat(5, 5, keys.keyMat1);
	showMat(5, 5, keys.keyMat2);

	char c1 = '0', c2 = '0'; 
	int i = 0, j = 0;

	while(i<textLength) {
		c1 = plainText[i];
		if (!isAlphabet(c1)) {
			cipheredText[i++] = c1;
		} else {
			j = i++; // j stocke l'indice de c1
			while(!isAlphabet(c2 = plainText[i])) cipheredText[i++] = c2;

			twoSquareDigraphEncr(keys, &c1, &c2);

			cipheredText[j]   = c1;
			cipheredText[i++] = c2;
		}
	}
	free(keyMat1);
	free(keyMat2);
	return cipheredText;
}

char* twoSquareEncr(const char* key1, const char* key2, const char* plainText) {
	return twoSquare(key1, key2, plainText);  
}

char* twoSquareDecr(const char* key1, const char* key2, const char* cipheredText) {
	return twoSquare(key1, key2, cipheredText);  
}

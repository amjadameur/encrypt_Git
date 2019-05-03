#include "str.h"

///Basic functions//////////////////////////////////////////////////////////////////
int* alter_tab_sign(int n, const int* tab) {
	int* alteredTab = (int*) malloc(sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		alteredTab[i] = -tab[i];
	}
	return alteredTab;
}

char upperC(char c) {
	return (c >= 'a' && c <= 'z') ? c-LOWER_UPPERCASE_OFFSET : c;
}

char lowerC(char c) {
	return (c >= 'A' && c <= 'A') ? c+LOWER_UPPERCASE_OFFSET : c;
}

char* upperStr(char* strIn) {
	unsigned int strLength = strlen(strIn);
	char *strOut = (char*) malloc((strLength+1)*sizeof(char));
	for (int i = 0; i < strLength; ++i)	{
		strOut[i] = upperC(strIn[i]);
	}
	return strOut;
}

void cpy_int_tab(int n, int* tab_d, int* tab_s) {
	for (int i = 0; i < n; ++i)
	{
		tab_d[i] = tab_s[i];
	}
}

unsigned char shiftLetter(const char original_letter, int shift_amount)
{
	unsigned char encrypted_letter = original_letter;

	if (encrypted_letter >= 'a' && encrypted_letter <= 'z')
	{
		encrypted_letter += shift_amount;
		
		if (encrypted_letter > 'z') {
			encrypted_letter = 'a' + (encrypted_letter - 'z' - 1);
		}

		else if (encrypted_letter < 'a') {
			encrypted_letter = 'z' - ('a' - encrypted_letter - 1); 
		}
	}

	else if (encrypted_letter >= 'A' && encrypted_letter <= 'Z')
	{
		encrypted_letter += shift_amount;
		
		if (encrypted_letter > 'Z') {
			encrypted_letter = 'A' + (encrypted_letter - 'Z' - 1);
		}

		else if (encrypted_letter < 'A') {
			encrypted_letter = 'Z' - ('A' - encrypted_letter - 1); 
		}
	}

	return encrypted_letter;
}	

///////////////////////////////////////////////////////////////////////////////////
int char_to_int(char letter) 
{
	int index = 0;
	if (letter >= 'a' && letter <= 'z')
	{
		index = letter - 'a';
	}
	else if (letter >= 'A' && letter <= 'Z')
	{
		index = letter -'A';
	}
	return index;
}

int* str_to_int(const char* key) {
	unsigned int keyLength = strlen(key);
	int* intKey = (int*) malloc(sizeof(int)*keyLength);
	for (int i = 0; i<keyLength; ++i) {
		intKey[i] = char_to_int(key[i]);
	}	
	return intKey;
}

char* int_to_str(int nb, const int* tab) {
	char* key = (char*) malloc((nb+1)*sizeof(char));
	for (int i = 0; i < nb; ++i) {
		key[i] = 'a' + tab[i];
	}
	return key;
}


///Find Char//////////////////////////////////////////////////////////////////////
bool char_in_str(char c, char* s) {
	unsigned int s_length = strlen(s);
	for (int i = 0; i < s_length; ++i)
	{
		if(s[i] == c) {
			return true;
			break;
		}
	}
	return false;
}

bool char_in_alphabets(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/////////////////////////////////////////////////////////////////////////////////////
char* removeDuplicates(const char* strIn) {
	unsigned int strInLength = strlen(strIn);
	char currentC;
	unsigned int strOutLength = 0;
	char *strOut = (char*) malloc((strInLength+1)*sizeof(char));
	strOut[0] = '\0';
	for (int i = 0; i < strInLength; ++i) {
		currentC = strIn[i];
		if (char_in_alphabets(currentC) && !char_in_str(currentC, strOut)) {
			strOut[strOutLength++] = strIn[i];
		}
	}
	strOut[strOutLength]='\0'; 	
	strOut = (char*) realloc(strOut, (strOutLength+1)*sizeof(char)); 	
	return strOut;
}

int* randIntKey(unsigned int keyLength) {
	int* intKey = (int*) malloc(keyLength*sizeof(int));
	int randVal;
	for (int i = 0; i < keyLength; ++i) {
		randVal = rand() % NB_LETTERS;
		intKey[i] = randVal;
	}
	return intKey;
}
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

void cpy_int_tab(int n, int* tab_d, int* tab_s) {
	for (int i = 0; i < n; ++i)
	{
		tab_d[i] = tab_s[i];
	}
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

char* lowerStr(char* strIn) {
	unsigned int strLength = strlen(strIn);
	char *strOut = (char*) malloc((strLength+1)*sizeof(char));
	for (int i = 0; i < strLength; ++i)	{
		strOut[i] = lowerC(strIn[i]);
	}
	return strOut;
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

bool isAlphabet(char c) {
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
		if (isAlphabet(currentC) && !char_in_str(currentC, strOut)) {
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

char shiftLetter(int shiftAmount, char cToShift)
{
	bool isLowerCase = false;
	if (!isAlphabet(cToShift)) return cToShift;
	
	// on fait l'opération en upper case
	if (cToShift >= 'a' && cToShift <= 'a') {
		isLowerCase = true;
		cToShift = upperC(cToShift);
	}

	cToShift += shiftAmount;

	if (cToShift > 'Z') {
		cToShift = 'A' + (cToShift - 'Z' - 1);
	}

	else if (cToShift < 'A') {
		cToShift = 'Z' - ('A' - cToShift - 1); 
	}
	
	return (isLowerCase == true) ? lowerC(cToShift) : cToShift;
}	


#include "encryption.h"


int main(int argc, char const *argv[])
{
	char plainText[] = "amjad";
	//char* cipheredText = caesarCipher(1, plainText);
	char* cipheredText = vigenere("ab", plainText);

	printf("%s\n", cipheredText);
	return 0;
}
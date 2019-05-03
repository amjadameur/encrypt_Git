

#include "encryption.h"




void test(void) {
	char **keyMat = keyMatGen("hello world", 'q');
	showMat(5, 5, keyMat);
	freeMat(5, keyMat);

}

int main(int argc, char const *argv[])
{
	char* plainText = "hide the gold";
/*	int* key;

	char * cipheredText  = oneTimePadEncr(&key, plainText);
	char * decryptedText = oneTimePadDecr(key, cipheredText);
	
	printf("%s\n", cipheredText);
	printf("%s\n", decryptedText);
*/
/*	char* key = "hello world";
	char* cipheredText;
	char* decryptedText;
	cipheredText  = playfair_cipher(ENCRYPTION, key, plainText);
	decryptedText = playfair_cipher(DECRYPTION, key, cipheredText);
	
	printf("%s\n", plainText);
	printf("%s\n", cipheredText);
	printf("%s\n", decryptedText);
*/
	test();
	return 0;
}
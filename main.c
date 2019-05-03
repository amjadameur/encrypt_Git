

#include "encryption.h"


void func(int**tab) {
	//printf("addr tab : %p\n", tab);

	*tab = (int*) malloc(sizeof(int));

	//printf("addr tab : %p\n", tab);

}

void test(void) {
	int* tab;
	printf("addr tab : %p\n", tab);
	func(&tab);

	printf("addr tab : %p\n", tab);

	free(tab);	
}

int main(int argc, char const *argv[])
{
	char* plainText = "amjad";
	int* key;

	char * cipheredText  = oneTimePadEncr(&key, plainText);
	char * decryptedText = oneTimePadDecr(key, cipheredText);
	
	printf("%s\n", cipheredText);
	printf("%s\n", decryptedText);



	//test();
	return 0;
}
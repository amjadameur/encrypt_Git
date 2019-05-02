#include "str.h"

///Basic functions//////////////////////////////////////////////////////////////////
void alter_tab_sign(int n, int* tab) {
	for (int i = 0; i < n; ++i)
	{
		tab[i] = -tab[i];
	}
}

int next_char(int index, char* s) {
	unsigned int s_length = strlen(s);
	char next_c;
	for (int i = index+1; i < s_length; ++i)
	{
		next_c = s[i];
		if (next_c != ' ') {
			return (char_in_alphabets(next_c)) ? i : 0;
		}
	}
	return 0;
}

char char_lower_to_uppercase(char c) {
	char upper_c;
	if (c >= 'a' && c <= 'z')	{
		upper_c = c-LOWER_UPPERCASE_OFFSET;
	}
	return upper_c;
	
}

void lower_to_uppercase(char* s) {
	unsigned int s_length = strlen(s);
	for (int i = 0; i < s_length; ++i)
	{
		if (s[i] >= 'a' && s[i] <= 'z')	{
			s[i] -= LOWER_UPPERCASE_OFFSET;
		}
	}
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

int* str_to_int(char* key) {
	unsigned int keyLength = strlen(key);
	int* intKey = (int*) malloc(sizeof(int)*keyLength);
	for (int i = 0; i<keyLength; ++i) {
		intKey[i] = char_to_int(key[i]);
	}	
	return intKey;
}

char* int_to_str(int nb, int* tab) {
	char* key = (char*) malloc((nb+1)*sizeof(char));
	for (int i = 0; i < nb; ++i) {
		key[i] = 'a' + tab[i];
	}
	return key;
}


///Find Char//////////////////////////////////////////////////////////////////////
int char_in_str(char c, char* s) {
	unsigned int s_length = strlen(s);
	for (int i = 0; i < s_length; ++i)
	{
		if(s[i] == c) {
			return 1;
			break;
		}
	}
	return 0;
}

int char_in_alphabets(char c) {
	int c_in_alphab = 0;
	char alphab;
	for (alphab = 'A'; alphab < 'Z'+1; ++alphab) {
		if (alphab == c) {
			c_in_alphab = 1;
			break;
		}
	}
	return c_in_alphab;
}

/////////////////////////////////////////////////////////////////////////////////////
void remove_duplicates(const char* key_i, char* key_o) {
	unsigned int key_length = strlen(key_i);
	char current_c;
	int key_o_length = 0;

	key_o[0] = '\0';
	for (int i = 0; i < key_length; ++i) {
		current_c = key_i[i];
		if (char_in_alphabets(current_c) && !char_in_str(current_c, key_o)) {
			key_o[key_o_length++] = key_i[i];
		}
	}
	key_o[key_o_length]='\0';
}

char pick_from_alphabets(char* offset, char* s, char except_c) {
	char picked_char = *offset;
	for (picked_char = *offset; picked_char < 'Z'+1; ++picked_char){
		if (!char_in_str(picked_char, s) && picked_char != except_c)
		{
			*offset = picked_char+1; 
			break;
		}
	}
	return picked_char;
}

void fill_blank_space(int start_index, int stop_index, char* processed_text) {
	for (int i = start_index; i < stop_index+1; ++i)
	{
		processed_text[i] = ' ';
	}
}


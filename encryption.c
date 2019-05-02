#include "encryption.h"

//CAESAR CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
void caesar_cipher(int key, const char* original_text_i, char* processed_text) {
	unsigned int text_length = strlen(original_text_i);
	char original_text[text_length];
	char original_letter;
	unsigned char encrypted_letter;
	int  shift_amount = key;

	strcpy(original_text, original_text_i);
	for (int i = 0; original_text[i] != '\0'; i++)
	{
		original_letter = original_text[i];
		encrypted_letter = shift_letter(original_letter, shift_amount);
		processed_text[i] = encrypted_letter;
	}
}

//VIGENERE CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
void vigenere_cipher(int key_length, const int* key_i, const char* original_text_i, char* processed_text) 
{
	int key[key_length];
	unsigned int text_length = strlen(original_text_i);
	char original_text[text_length];
	char original_letter;
	unsigned char encrypted_letter;
	int shift_amount;

	cpy_int_tab(key_length, key, key_i);
	strcpy(original_text, original_text_i);
	for (int i = 0; i<text_length; i+=key_length) {
		for (int j = 0; j<key_length; j++) {
			if (original_text[i+j] == '\0') {
				break;
			} else {
				original_letter = original_text[i+j];
				shift_amount = key[j];
				encrypted_letter = shift_letter(original_letter, shift_amount);
				processed_text[i+j] = encrypted_letter;
			}
		}	
	}
}

//ONE TIME PAD CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
void generate_one_time_pad_key(unsigned int original_text_length, int* one_time_pad_key) {
	int r;
	for (int i = 0; i < original_text_length; ++i)
	{
		r = rand() % NB_LETTERS;
		one_time_pad_key[i] = r;
	}
}

void one_time_pad_cipher(unsigned int original_text_length, const int* one_time_pad_key_i, const char* original_text_i, char* processed_text) {
	int key[original_text_length];
	char original_text[original_text_length];	
	int shift_amount;
	char original_letter;
	unsigned char encrypted_letter; 

	//Pre-treatment
	cpy_int_tab(original_text_length, key, one_time_pad_key_i);
	strcpy(original_text, original_text_i);

	for (int i = 0; i < original_text_length; ++i)
	{
		shift_amount = key[i];
		original_letter = original_text[i];
		encrypted_letter = shift_letter(original_letter, shift_amount);
		processed_text[i] = encrypted_letter;
	}	
}

//PLAYFAIR CIPHER///////////////////////////////////////////////////////////////////////////////////////////////
void encrypt_playfair_bigraph(int encrypt_decrypt, char playfair_key[][PLAYFAIR_R_C_SIZE], int* bigraph_coordinates_c1, int* bigraph_coordinates_c2, char* encr_c1, char* encr_c2) {
	int c1_r = bigraph_coordinates_c1[0];
	int c1_c = bigraph_coordinates_c1[1];
	int c2_r = bigraph_coordinates_c2[0];
	int c2_c = bigraph_coordinates_c2[1];

	if (c1_c == c2_c && c1_r == c2_r) {
		*encr_c1 = playfair_key[c1_r][c1_c];
		*encr_c2 = playfair_key[c2_r][c2_c];
	}
	else if (c1_r == c2_r) {
		if (c1_c == PLAYFAIR_R_C_SIZE-1 || encrypt_decrypt == DECRYPTION) {
			*encr_c1 = playfair_key[c1_r][c1_c-1];
		} else {
			*encr_c1 = playfair_key[c1_r][c1_c+1];
		}

		if (c2_c == PLAYFAIR_R_C_SIZE || encrypt_decrypt == DECRYPTION) {
			*encr_c2 = playfair_key[c2_r][c2_c-1];
		} else {
			*encr_c2 = playfair_key[c2_r][c2_c+1];
		}
	}

	else if (c1_c == c2_c) {
		if (c1_r == PLAYFAIR_R_C_SIZE-1 || encrypt_decrypt == DECRYPTION) {
			*encr_c1 = playfair_key[c1_r-1][c1_c];
		} else {
			*encr_c1 = playfair_key[c1_r+1][c1_c];
		}

		if (c2_r == PLAYFAIR_R_C_SIZE-1 || encrypt_decrypt == DECRYPTION) {
			*encr_c2 = playfair_key[c2_r-1][c2_c];
		} else {
			*encr_c2 = playfair_key[c2_r+1][c2_c];
		}

	} else {
		*encr_c1 = playfair_key[c1_r][c2_c];
		*encr_c2 = playfair_key[c2_r][c1_c];
	}
}

void playfair_cipher(int encrypt_decrypt, const char* key_i, const char* original_text_i, char* processed_text) {
	char playfair_key[PLAYFAIR_R_C_SIZE][PLAYFAIR_R_C_SIZE];
	unsigned int original_text_length = strlen(original_text_i);
	char original_text[original_text_length];
	char key[strlen(key_i)];
	int i = 0;
	char to_encr_c1, to_encr_c2;
	char encr_c1, encr_c2;
	int to_encr_c2_index;
	int bigraph_coordinates_c1[BIGRAPH_SIZE];
	int bigraph_coordinates_c2[BIGRAPH_SIZE];

    // pre-treatment
	strcpy(original_text, original_text_i);
	strcpy(key, key_i);
	matrix_key_generator(key, playfair_key, 'Q');
	lower_to_uppercase(original_text);

	while(i<original_text_length) {
		to_encr_c1 = original_text[i];
		to_encr_c2_index = next_char(i, original_text);
		if(!char_in_alphabets(to_encr_c1) || !to_encr_c2_index) {
			processed_text[i] = original_text[i];
			i++;
		} else {
			to_encr_c2 = original_text[to_encr_c2_index];
			char_matrix_coordinates(playfair_key, to_encr_c1, bigraph_coordinates_c1);
			char_matrix_coordinates(playfair_key, to_encr_c2, bigraph_coordinates_c2);
			encrypt_playfair_bigraph(encrypt_decrypt, playfair_key, bigraph_coordinates_c1, bigraph_coordinates_c2, &encr_c1, &encr_c2); 
			fill_blank_space(i+1, to_encr_c2_index-1, processed_text);
			processed_text[to_encr_c2_index] = encr_c2;
			processed_text[i]                = encr_c1;
			i = to_encr_c2_index+1;
		}
	}
}

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
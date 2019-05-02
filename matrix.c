#include "matrix.h"

///MATRIX OPERATIONS///////////////////////////////////////////////////////////////////////////
void alphabet_matrix_generator(char alphabet_matrix[][PLAYFAIR_R_C_SIZE], char except_c) {
	char current_letter = 'A';
	except_c = char_lower_to_uppercase(except_c);
	for (int r = 0; r < PLAYFAIR_R_C_SIZE; ++r) {
		for (int c = 0; c < PLAYFAIR_R_C_SIZE; ++c) {
			if (current_letter == except_c) {
				current_letter++;
			}
			alphabet_matrix[r][c] = current_letter;
			current_letter++;
		}		
	}
}


void matrix_key_generator(const char* key_i, char key_matrix[][PLAYFAIR_R_C_SIZE], char except_c) {
	unsigned int key_length = strlen(key_i);
	char raw_key[key_length];
	char key[MAX_STR];
	int c_index;
	char offset = 'A';
	int alphab_pick = 0;

	// Pre-treatment
	strcpy(raw_key, key_i);
	strcpy(key,     key_i);
	lower_to_uppercase(raw_key);
	remove_duplicates(raw_key, key);

	for (int i = 0; i < PLAYFAIR_R_C_SIZE; ++i) {
		for (int j = 0; j < PLAYFAIR_R_C_SIZE; ++j) {
			c_index = PLAYFAIR_R_C_SIZE*i+j;
			if (!alphab_pick && key[c_index]!='\0') {
				key_matrix[i][j] = key[c_index];
			}
			else {
				alphab_pick = 1;
				key_matrix[i][j] = pick_from_alphabets(&offset, key, except_c);
			}			
		}
	} 
}


void char_matrix_coordinates(const char playfair_key[][PLAYFAIR_R_C_SIZE], const char c_to_find, int* c_coordinates) {
	for (int r = 0; r < PLAYFAIR_R_C_SIZE; ++r) {
		for (int c = 0; c < PLAYFAIR_R_C_SIZE; ++c)	{
			if (c_to_find == playfair_key[r][c]) {
				c_coordinates[0] = r;
				c_coordinates[1] = c;
				goto c_found;
			}
		}
	}
	c_found:;
}


void show_matrix(const char matrix[][PLAYFAIR_R_C_SIZE]) {
	for (int r = 0; r < PLAYFAIR_R_C_SIZE; ++r) {
		for (int c = 0; c < PLAYFAIR_R_C_SIZE; ++c) {
			printf("%c ", matrix[r][c]);
		}
		NEWLINE;
	}
	NEWLINE;
}




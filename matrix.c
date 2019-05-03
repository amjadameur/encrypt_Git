#include "matrix.h"

char** allocCharMat(int rows, int cols) {
	char **keyMatrix = (char**) malloc(rows*sizeof(char*));
	for (int r = 0; r < rows; ++r) {
		keyMatrix[r] = (char*) malloc(cols*sizeof(char));
	}
	return keyMatrix;
}

void freeMat(int rows, char **matrix) {
	for (int r = 0; r < rows; ++r) {
		free(matrix[r]);
	}
	free(matrix);
}

void showMat(int rows, int cols, const char** matrix) {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			printf("%c ", matrix[r][c]);
		}
		NEWLINE;
	}
	NEWLINE;
}

///MATRIX OPERATIONS///////////////////////////////////////////////////////////////////////////
char** alphabMatGen(char exceptC) {
	char **matrix = allocCharMat(PLAYFAIR_R_C_SIZE, PLAYFAIR_R_C_SIZE);
	char currentC = 'A';
	exceptC = upperC(exceptC);
	for (int r = 0; r < PLAYFAIR_R_C_SIZE; ++r) {
		for (int c = 0; c < PLAYFAIR_R_C_SIZE; ++c) {
			if (currentC == exceptC) currentC++;
			matrix[r][c] = currentC++;
		}		
	}
	return matrix;
}

char** keyMatGen(const char* key, char exceptC) {
	char **keyMatrix = allocCharMat(PLAYFAIR_R_C_SIZE, PLAYFAIR_R_C_SIZE);
	char *upperKey, *heapCleaner;
	int currentIdx = 0;
	char alphabLetter = 'A';
	bool alphabPick = false;
	exceptC = upperC(exceptC);

	// Pre-treatment
	upperKey    = removeDuplicates(key);
	heapCleaner = upperKey;
	upperKey    = upperStr(upperKey);
	free(heapCleaner);

	for (int i = 0; i < PLAYFAIR_R_C_SIZE; ++i) {
		for (int j = 0; j < PLAYFAIR_R_C_SIZE; ++j) {	
			if (!alphabPick && upperKey[currentIdx]!='\0') {
				keyMatrix[i][j] = upperKey[currentIdx++];
				if(upperKey[currentIdx]=='\0') alphabPick = true;
			}
			else {
				while(char_in_str(alphabLetter, upperKey) == true || alphabLetter==exceptC) alphabLetter++;
				keyMatrix[i][j] = alphabLetter++;
			}			
		}
	} 
	return keyMatrix;
}

void findCharInMat(const char **mat, char charToFind, int* row, int* col) {
	*row = 0; *col = 0;
	for (int r = 0; r < FIVE_ROWS; ++r) {
		for (int c = 0; c < FIVE_COLUMNS; ++c)	{
			if (mat[r][c] == charToFind) {
				*row = r;
				*col = c;
				return;
			}
		}
	}
}






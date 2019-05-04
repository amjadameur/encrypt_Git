#include "matrix.h"

char droppedLetter = 'q';

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
char** alphabMatGen() {
	char **matrix = allocCharMat(FIVE_ROWS, FIVE_COLUMNS);
	char currentC = 'A';
	droppedLetter = upperC(droppedLetter);
	for (int r = 0; r < FIVE_ROWS; ++r) {
		for (int c = 0; c < FIVE_COLUMNS; ++c) {
			if (currentC == droppedLetter) currentC++;
			matrix[r][c] = currentC++;
		}		
	}
	return matrix;
}

char** keyMatGen(const char* key) {
	char **keyMatrix = allocCharMat(FIVE_ROWS, FIVE_COLUMNS);
	char *upperKey, *heapCleaner;
	int currentIdx = 0;
	char alphabLetter = 'A';
	bool alphabPick = false;
	droppedLetter = upperC(droppedLetter);

	// Pre-treatment
	upperKey    = removeDuplicates(key);
	heapCleaner = upperKey;
	upperKey    = upperStr(upperKey);
	free(heapCleaner);

	for (int i = 0; i < FIVE_ROWS; ++i) {
		for (int j = 0; j < FIVE_COLUMNS; ++j) {	
			if (!alphabPick && upperKey[currentIdx]!='\0') {
				keyMatrix[i][j] = upperKey[currentIdx++];
				if(upperKey[currentIdx]=='\0') alphabPick = true;
			}
			else {
				while(char_in_str(alphabLetter, upperKey) == true || alphabLetter==droppedLetter) alphabLetter++;
				keyMatrix[i][j] = alphabLetter++;
			}			
		}
	} 
	return keyMatrix;
}

void findCharInKeyMat(const char **mat, char charToFind, int* row, int* col) {
	*row = 0; *col = 0;
	charToFind = upperC(charToFind);
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






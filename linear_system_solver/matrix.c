#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

SS_Matrix *newMatrix(int nrows, int ncols) {
	SS_Matrix *matrix = (SS_Matrix*) malloc(sizeof(SS_Matrix));
	
	matrix->entries = malloc(sizeof(double*) * nrows);
	
	matrix->nrows = nrows;
	matrix->ncols = ncols;
	
	int i;
	
	for (i = 0; i < nrows; i++) {
		matrix->entries[i] = malloc(sizeof(double) * ncols);
	}
	
	return matrix;
};

/** Zeroes out a matrix*/
void zeroMatrix(SS_Matrix *matrix) {
	int row, col;
	
	for (row = 0; row < matrix->nrows; row++) {
		for (col = 0; col < matrix->ncols; col++) {
			matrix->entries[row][col] = 0;
		}
	}
}

double determinant(SS_Matrix *matrix) {
	if (matrix->nrows != matrix->ncols) {
		printf("Not a square matrix!\n");
		return -1024;
	}
	
	if (matrix->nrows == 2 && matrix->ncols == 2) {
		// we simply use the base case
		return at(matrix, 0, 0) * at(matrix, 1, 1) - at(matrix, 0, 1) * at(matrix, 1, 0);
	}
	
	if (matrix->nrows == 1 && matrix->ncols == 1) {
		return at(matrix, 0, 0);
	}
	
	// otherwise we loop across the top rows and remove elements
	int col;
	
	// the sign
	int sign = -1;
	
	// our sum
	double sum = 0;
	
	SS_Matrix *subset_matrix = NULL;
	for (col = 0; col < matrix->ncols; col++) {
		sign *= -1; // keep sign flipping back and forth
		
		// delete the current column and do the determinant again
 		subset_matrix = newMatrix(matrix->nrows - 1, matrix->ncols - 1);
		
		subset(matrix, subset_matrix, 0, col);
		
		// now take the determinant recursively
		sum += sign * at(matrix, 0, col) * determinant(subset_matrix);
		
		freeMatrix(subset_matrix);
		subset_matrix = NULL;
	}
	
	return sum;
};

void subset(SS_Matrix *src, SS_Matrix *dst, int row, int col) {
	
	int r, c;
	
	// we need to adjust the indicies appropriately
	int adjC = 0;
	int adjR = 0;
	
	for (r = 0; r < src->nrows; r++) {
		// copy all the entries of this row over (-1 is wildcard)
		if (r != row || r == -1) {
			// reset
			adjC = 0;
			
			// please note my subtle shoutout to C++ ;)
			for (c = 0; c < src->ncols; c++) {
				// copy the column over if we aren't trying to remove it (-1 is wildcard)
				
				if (c != col || col == -1) {
					dst->entries[adjR][adjC] = src->entries[r][c];
					adjC++; // we copied another column
				}
			}
			
			adjR++; // we copied another row
		}

	}
};

void freeMatrix(SS_Matrix *matrix) {
	// free the coefficients first
	int row;
	
	for (row = 0; row < matrix->nrows; row++) {
		free(matrix->entries[row]);
	}
	
	// now free the array of pointers
	free(matrix->entries);
	
	// now free the entire structure
	free(matrix);
}
void addRow(SS_Matrix *matrix, int srcRow, int destRow) {
	int col;
	
	for (col = 0; col < matrix->ncols; col++) {
		matrix->entries[destRow][col] += matrix->entries[srcRow][col];
	}
}

/** Reads a matrix in on the command line */
SS_Matrix* readMatrix() {
	printf("Please enter the number of variables followed by the augmented matrix: \n");
	
	int numberOfVariables;
	scanf("%d", &numberOfVariables);
	
	int row, col;
	
	// we have an extra row for the augmented equality signs
	SS_Matrix *matrix = newMatrix(numberOfVariables, numberOfVariables + 1);
	
	for (row = 0; row < numberOfVariables; row++) {
		for (col = 0; col < numberOfVariables + 1; col++) {
			scanf("%lf", &matrix->entries[row][col]);
		}
	}
	
	
	return matrix;
}
void printMatrix(SS_Matrix *matrix) {
	int col, row;
	
	
	for (row = 0; row < matrix->nrows; row++) {
		
		for (col = 0; col < matrix->ncols; col++) {
			printf("%.2lf\t", matrix->entries[row][col]);
		}
		
		printf("\n");
	}
};

void printMathematicaMatrix(SS_Matrix *matrix) {
	int col, row;
	
	printf("= {\n");
	
	for (row = 0; row < matrix->nrows; row++) {
		
		printf("{");
		for (col = 0; col < matrix->ncols; col++) {
			
			if (col != matrix->ncols - 1) {
				// print a comma until last column
				printf("%.4lf, ", matrix->entries[row][col]);
			} else {
				// last column, don't print a comman
				printf("%.4lf", matrix->entries[row][col]);
			}

		}
		
		
		if (row != matrix->nrows - 1) {
			printf("}, \n"); // if not the last row, print a comma
		} else {
			printf("}\n"); // if the last row, don't print a comma
		}
		
	}
	
	printf("}\n");
}

void swapRows(SS_Matrix *matrix, int row1, int row2) {
	int col;
	
	for (col = 0; col < matrix->ncols; col++) {
		int tempRow1Entry = matrix->entries[row1][col];
		
		matrix->entries[row1][col] = matrix->entries[row2][col];
		matrix->entries[row2][col] = tempRow1Entry;
	}
}

void multiplyRow(SS_Matrix *matrix, int row, double coefficient) {
	int col;
	
	for (col = 0; col < matrix->ncols; col++) {
		matrix->entries[row][col] = matrix->entries[row][col] * coefficient;
	}
}

double at(SS_Matrix *matrix, int row, int column) {
	if (matrix->entries == NULL)
		return -1;
		
	return matrix->entries[row][column];
}

void setAt(SS_Matrix *matrix, int row, int column, double val) {
	if (matrix->entries == NULL)
		return;
	
	matrix->entries[row][column] = val;
}
void multiplyEntries(SS_Matrix *matrix, double scaler) {
	int col, row;
	
	for (row = 0; row < matrix->nrows; row++) {
		for (col = 0; col < matrix->ncols; col++) {
			matrix->entries[row][col] *= scaler;
		}
	}
}

SS_Matrix *augment(SS_Matrix *left, SS_Matrix *right) {
	if (left->nrows != right->nrows) {
		return NULL;
	}
	
	SS_Matrix *augmented = newMatrix(left->nrows, left->ncols + right->ncols);
	
	// copy in the first matrix
	int col, row;
	
	for (row = 0; row < left->nrows; row++) {
		for (col = 0; col < left->ncols; col++) {
			augmented->entries[row][col] = left->entries[row][col];
		}
	}
	
	// start where the other matrix left off	
	// (one column to the right)
	int offset = left->ncols;
	
	// copy in the second matrix
	for (row = 0; row < left->nrows; row++) {
		for (col = offset; col < offset + right->ncols; col++) {
			augmented->entries[row][col] = right->entries[row][col - offset];
		}
	}
	
	return augmented;
}

void multiplyAndAddRow(SS_Matrix *matrix, int srcRow, int destRow, double coefficient) {
	int col;
	
	// if the coefficient is zero, ignore because we aren't doing anything
	if (coefficient == 0) {
		return;
	}
	
	for (col = 0; col < matrix->ncols; col++) {
		matrix->entries[destRow][col] += coefficient * matrix->entries[srcRow][col];
	}
}
#ifndef MATRIX_H
#define MATRIX_H

/** A simple structure representing a matrix
*/
typedef struct {
	/** our 2D array of coefficients */
	double **entries;
	int nrows;
	int ncols;
} SS_Matrix;

/** Prints out the given matrix*/
void printMatrix(SS_Matrix *matrix);

/** Prints matrix in mathematica format */
void printMathematicaMatrix(SS_Matrix *matrix);

/** Reads in a matrix from Jeff's test case and fills in the matrix.*/
SS_Matrix* readMatrix();

/** Swaps two rows in a given matrix*/
void swapRows(SS_Matrix *matrix, int row1, int row2);

/** Zeroes out a matrix*/
void zeroMatrix(SS_Matrix *matrix);

/** Takes a subset of the given matrix. pass in -1 if you don't want a row or column removed*/
void subset(SS_Matrix *src, SS_Matrix *dst, int row, int col);

/** Takes the determinant of a given matrix */
double determinant(SS_Matrix *matrix);

/** gets the entry of the given matrix at the specified row and column*/
double at(SS_Matrix *matrix, int row, int column);

/** sets the entry of the given matrix at the specified row and column*/
void setAt(SS_Matrix *matrix, int row, int column, double val);

/** multiplies then adds a row*/
void multiplyAndAddRow(SS_Matrix *matrix, int srcRow, int destRow, double coefficient);

/** multiplies each individual entry by a scalar */
void multiplyEntries(SS_Matrix *matrix, double scaler);

/** Adds two row together. It adds the srcRow into the destRow. */
void addRow(SS_Matrix *matrix, int srcRow, int destRow);

/** Augments one matrix with another and returns a new matrix. It is your job to delete the old matrices.*/
SS_Matrix *augment(SS_Matrix *left, SS_Matrix *right);

/**multiplies the given row by the specified coefficient*/
void multiplyRow(SS_Matrix *matrix, int row, double coefficient);

/**
* Creates a new matrix with the specified rows and columns
*/
SS_Matrix *newMatrix(int nrows, int ncols);

/**
* Frees the given matrix
*/
void freeMatrix(SS_Matrix *matrix);	
#endif
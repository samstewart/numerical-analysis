#include "linear_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include "substitution.h"
#include <math.h>


/*
* Since we are using this as a static librar, we comment out main
int main(int argc, const char* args[]) {
	
	SS_Matrix *matrix = readMatrix();
	
	printMathematicaMatrix(matrix);
	
	if (matrix->nrows == 1) {
		printf("Trivial solution: %.5lf\n", at(matrix, 0, 1)/at(matrix, 0, 0));
	}

	// we use the number of rows because that is the number of variables (otherwise underdetermined)
	double *solns = malloc(sizeof(double) * matrix->nrows);
	
	int totalSolns = solveLinearSystem(matrix, solns);
	
	if (totalSolns == 0) {
		printf("No unique solutions\n");
		return 1;
	}
	
	int soln;
	
	printf("----------------------\n\n");
	printf("Total solutions: %d\n", totalSolns);
	
	// we have to work backward due to strange ordering (I will change that in the future)
	for (soln = 0; soln < totalSolns; soln++) {
		// the lower solutions are at the end of the matrix so we have to reverse the index
		printf("X%d %.5lf\n", soln, solns[soln]);
	}
	printf("----------------------\n\n");
		
	freeMatrix(matrix);
	
	return 0;
}
*/

void checkDeterminant(SS_Matrix *matrix) {
	// check to see if we actually have some solutions
	SS_Matrix *non_augmented = newMatrix(matrix->nrows, matrix->ncols - 1);
	

	// remove the last column
	subset(matrix, non_augmented, -1, matrix->ncols - 1);
	
	double det = determinant(non_augmented);
	printf("Det: %.5lf\n", det);
	
	freeMatrix(non_augmented);
		
	if (fabs(det) < .00000001) {
		printf("No solutions or infinitely many!\n");
		exit(1);
	}
};

/** 
* Attempts to solve a linear system of equations specified in the matrix. 
* Returns the number of solutions.
* Solutions are indexed so that the "lowest" one is at the highest index.
*/
int solveLinearSystem(SS_Matrix *matrix, double *solutions) {
	
	// now we do simple guassian row reduction
	int i, j;
	
	int numberOfVars = matrix->nrows;
	
	double pivot, factor;
	
	// don't go all the way to the last column
	// find a row as a pivot, then add it to all the other rows
	for (i = 0; i < numberOfVars - 1; i++) {
		
		// we are finding the pivot, but it should be nonzero
		pivot = at(matrix, i, i);
		
		// go *down* the matrix in search of a nonzero pivot and swap it up
		if (fabs(pivot) < .000001) {
			int k;
			
			// look at the other rows, any better options?
			for (k = i + 1; k < numberOfVars && fabs(pivot) < .00000001; k++) {
				pivot = at(matrix, k, i);
			}
			

			// if we have hit the bottom without a non-zero however...
			if (fabs(pivot) < .00000001) {
				return 0; // no solutions
			}
			
			// we have to subtract off -1 because k is incremented once more
			swapRows(matrix, k - 1, i);
		}
		
		// now use this pivot row to eliminate zeros in the remaining rows
		for (j = i + 1; j < numberOfVars; j++) {
			// find the mulitple we need to add
			factor = at(matrix, j, i) / pivot;
			
			// now we update the appropriate row
			multiplyAndAddRow(matrix, i, j, -factor);
		}
	}

	
	return backSubstituteSolutions(matrix, solutions);
}
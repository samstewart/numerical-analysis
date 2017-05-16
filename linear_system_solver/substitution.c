#include "substitution.h"
#include "matrix.h"
#include <math.h>

int backSubstituteSolutions(SS_Matrix *matrix, double solns[]) {
	
	// now we do the backsubstitution
	// we index solutions from 0 to n - 1 where 0 is the variable closest to the augmented column (far right)
	
	// we work our way "up" the matrix
	int row, col;
	double curVarCoeff;
	
	double backSubSum;
	
	
	// must have the proper number of equations or will be underdetermined.
	// we start at the higher powers and work our way down (imagine starting at far left column; ignorning augmented column)
	int curSoln = (matrix->nrows - 1);
	
	// start the process by finding the first solution and placing it at the appropriate index
	curVarCoeff = at(matrix, matrix->nrows - 1, matrix->ncols - 2);
	
	if (fabs(curVarCoeff) < .000000001) {
		// infinitely many solutions
		return 0;
	}
	
	solns[curSoln] = at(matrix, matrix->nrows - 1, matrix->ncols - 1) / curVarCoeff;
	curSoln--;
	
	// start at the far right and work our way upwards
	for (row = (matrix->nrows - 1) - 1; row >= 0; row--) {
		curVarCoeff = at(matrix, row, row);
		
		if (fabs(curVarCoeff) < .000000001) {
			// infinitely many solutions
			return 0;
		}
		
		// start the sum with the far right value in the augmented column
		// that we want to add to the right hand side
		backSubSum = at(matrix, row, matrix->ncols - 1);
		
		// move other variables to the other side.
		// we subtract off one because we want to loop just through the other variables.
		// of course, we need to account for zero indexing
		for (col = (matrix->ncols - 1) - 1; col > row; col--) {
			// we have to flip the index for the solutions because the lowest
			// solution is at the lowest index
			backSubSum -= at(matrix, row, col) * solns[col];
		}
		
		// divide off the leading coefficient over the sum
		solns[curSoln] = backSubSum / curVarCoeff;
		curSoln--;
		
	}
	
	// since we always update curSoln *after* adding a solution, this should
	// have the proper +1 (or minus 1 in this case because we go one beyond)
	return (matrix->nrows - 1) - curSoln;
}


int forwardSubstituteSolutions(SS_Matrix *matrix, double solns[]) {
	return -1;
}
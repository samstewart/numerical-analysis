#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FPT.h"
#include "comprehensive_interpolation.h"
#include "matrix.h"

double linearRegression(double coeff[], double x) {
	return coeff[0] + coeff[1] * x;
}

double cubicSpline(CubicCoeff coeff[], int num_coeff, double x) {
	// find the interval we fall into
	// TODO: more efficient way to draw by just going through the points and picking interval once,
	// don't continually 'refind' the interval.
	int i = 0;
	
	for (i = 0; i < num_coeff; i++) {
		// we need a pointer to manipulate directly
		CubicCoeff *co = &coeff[i];
		
		// if the x is in a point interval, return the polynomial
		if (x > co->startP.x && x < co->endP.x) {
			double poly = co->startP.y + (co->endP.y - co->startP.y) / (co->endP.x - co->startP.x) * (x - co->startP.x);
			
			poly += (x - co->startP.x) * (x - co->endP.x) * (co->A + co->B * (x - co->startP.x));
			
			// disjoint intervals so won't match anymore
			return poly;
		}
	}
	
	return -1;
}

int findSplineCoefficients(Point points[], int num_points, CubicCoeff coeff[]) {
	if (num_points < 2) {
		return 0; // can't do anything useful yet
	}
	
	// we want num_points columns because (num_points - 1) * 2 (+ 1 for augmented matrix)
	// we double the number of rows because we need two sets of equations for each join
	// we need two rows for each middle join but only one row each for the endpoints.
	SS_Matrix *coeffMatrix = newMatrix((num_points - 2) * 2 + 2, (num_points - 1) * 2 + 1);
	
	zeroMatrix(coeffMatrix);
	// load this thing up with the data we'll need to solve for the coefficients.
	
	// set the endpoint contraints first
	
	// left endpoint
	setAt(coeffMatrix, 0, 0, 1);
	setAt(coeffMatrix, 0, 1, -(points[1].x - points[0].x));
	setAt(coeffMatrix, 0, coeffMatrix->ncols - 1, 0);
	
	// right endpoint
	setAt(coeffMatrix, coeffMatrix->nrows - 1, coeffMatrix->ncols - 3, 1);
	setAt(coeffMatrix, coeffMatrix->nrows - 1, coeffMatrix->ncols - 2, 2 * points[num_points - 1].x - points[num_points - 2].x);
	setAt(coeffMatrix, coeffMatrix->nrows - 1, coeffMatrix->ncols - 1, 0);
	
	// now we stick in the diagonal points
	// now we fill out the coeffs
	int col, row;
	

	for (row = 1; row < coeffMatrix->nrows - 1; row += 2) {
		/////////////////////////////////////////////////////
		/////////////////// Fill in the last column /////////
		col = coeffMatrix->ncols - 1;
		// move down the matrix in groups of 2
		int pointIndex = (row + 1) / 2;
		
		double val = points[pointIndex + 1].y - points[pointIndex].y;
		val /= points[pointIndex + 1].x - points[pointIndex].x;
		val -= (points[pointIndex].y - points[pointIndex - 1].y) / (points[pointIndex].x - points[pointIndex - 1].x);
		
		setAt(coeffMatrix, row, col,      val);
		
		// and now put in the negative of this
		setAt(coeffMatrix, row + 1, col, -val);
		
		//////////////////////////////////////////////////
		//////////// Middle Diagonal /////////////////////
		// TODO: collapse this into one pass
		// middle diagonal
		col = row;
		// move down the rows by groups of two (maybe better to just add two each time?)
		pointIndex = (row + 1) / 2;
		
		val = points[pointIndex].x - points[pointIndex - 1].x;
		
		setAt(coeffMatrix, row, col, val * val);
		
		// now stick the other term diagonally
		val = points[pointIndex + 1].x - points[pointIndex - 1].x;
		
		setAt(coeffMatrix, row + 1, col + 1, -val);
		
		///////////////////////////////////////////////////
		//////////////////// Top Diagonal /////////////////
		col = row + 1;
		// move down the rows by groups of two (maybe better to just add two each time?)
		pointIndex = (row + 1) / 2;
		val = points[pointIndex + 1].x - points[pointIndex].x;
		
		setAt(coeffMatrix, row, col, val);
		
		// now stick the other term diagonally
		double diagVal = val * (points[pointIndex].x - points[pointIndex - 1].x);
		
		setAt(coeffMatrix, row + 1, col + 1, diagVal);
		
		
		///////////////////////////////////////////////////
		///////////////// Bottom Diagonal /////////////////
		col = row - 1;
		// move down the rows by groups of two (maybe better to just add two each time?)
		pointIndex = (row + 1) / 2;
		
		val = points[pointIndex].x - points[pointIndex - 1].x;
		
		setAt(coeffMatrix, row, col, val);
		
		// now stick the other term diagonally
		// just square it
		diagVal = val * val;
		
		setAt(coeffMatrix, row + 1, col + 1, diagVal);
	}

	
	double *solns = malloc(sizeof(double) * (num_points - 1) * 2);
	
	// should have (num_points - 1)*2 solutions for our coefficients
	int totalSolns = solveLinearSystem(coeffMatrix, solns);
	
	int i;
	// now we build up the coefficients taking jumps of two at at time
	// since we have two per interval.
	for (i = 0; i < totalSolns; i += 2) {
		CubicCoeff *co = &coeff[i];
		
		co->A 		= solns[i];
		co->B 		= solns[i + 1];
		
		co->startP 	= points[i / 2];
		co->endP   	= points[i / 2 + 1];
		
	}
	free(solns);
	freeMatrix(coeffMatrix);
	
	return totalSolns;
}

void printCubicCoeff(CubicCoeff co) {
	printf("CubicCoeff: A: %.5lf B: %.5lf startX: %.5lf endX: %.5lf\n", co.A, co.B, co.startP.x, co.endP.x);
}

int findLinearCoefficients(Point points[], int num_points, double coeff[], int num_coeff) {
	// currently only finds the intercept and coefficient
	int i = 0;
	
	double y_mean = 0;
	double x_mean = 0;
	
	for (i = 0; i < num_points; i++) {
		y_mean += points[i].y;
		x_mean += points[i].x;
	}
	
	y_mean /= num_points;
	x_mean /= num_points;
	
	double numerator = 0;
	double denom = 0;
	
	for (i = 0; i < num_points; i++) {
		denom += pow((points[i].x - x_mean), 2);
		numerator += (points[i].x - x_mean)*(points[i].y - y_mean);
	}
	
	double beta_1 = numerator / denom;
	
	double beta_0 = y_mean - beta_1 * x_mean;
	coeff[0] = beta_0;
	coeff[1] = beta_1;
	
	return 2;
}

double fittedCurve(Point points[], int num_points, double x) {
	int i = 0;
	
	double sum = 0;
	
	// loop through all coefficients and construct lagrange interpolating polynomial
	// and evaluate it as we go along.
	for (i = 0; i < num_points; i++) {
		double cur_y = points[i].y;
		double cur_x = points[i].x;
		 
		// important to start these as 1, otherwise no joy!
		double denom 		= 1;
		double numerator 	= 1;
		
		int j = 0;
		
		// go through all the coefficients but avoid using ourselves
		for (j = 0; j < num_points; j++) {
			if (j != i) {
				numerator 	*= (x 		- points[j].x);
				denom 		*= (cur_x 	- points[j].x);
			}
		}
		

		sum += cur_y * (numerator / denom);
	}
	
	return sum;
}
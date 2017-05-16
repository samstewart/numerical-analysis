#include "linear_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include "substitution.h"
#include "newtons_multivariable.h"
#include "matrix.h"
#include <math.h>

#define CONVERGED_DELTA .0000001

/*
int main(int argc, const char* args[]) {
	
	printf("Newton's Method\n");
	
	// put together a system of equations
	Equation *equationForF = newEquation('x', 2);
	Equation *equationForG = newEquation('y', 2);
	
	equationForF->partials[0] = &partial_fx;
	equationForF->partials[1] = &partial_fy;
	equationForF->evaluate    = &func_f;
	
	equationForG->partials[0] = &partial_gx;
	equationForG->partials[1] = &partial_gy;
	equationForG->evaluate    = &func_g;
	
	Equation *equations[2] = {equationForF, equationForG};
	
	ZeroSystem *sys = newZeroSystem(equations, 2, 2);
	
	double *solns = malloc(sizeof(double) * 2);
	
	// initial guesses
	solns[0] = -5;
	solns[1] = -3;
	
	printf("Trying with initial guess (%lf, %lf)\n", solns[0], solns[1]);
	
	solve(sys, solns, 100);
	
	printf("Plugging back in (%.5lf %.5lf)\n", func_g(solns), func_f(solns));
	freeZeroSystem(sys);
	free(solns);
	return 0;
}
*/
///////////////////////////////////////////////////////////////
/////////// Partial derivatives and functions ////////////////

double partial_fx(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	return 2*cos(x - y) - 2*x*sin(x - y);
}

double partial_fy(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	return 2*x*sin(x - y);

}

double partial_gx(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	return 4*y*cos(x*y) - sin(x + y);
}

double partial_gy(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	4*x*cos(x*y) - sin(x + y);
}

double func_f(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	return 2*x*cos(x - y) - 1;
}

double func_g(double vars[]) {
	double x = vars[0];
	double y = vars[1];
	return cos(x + y) + 4*sin(x*y);
}

void stepByAddingLinearSolutions(double curVals[], double steps[], int numberOfEquations) {
	int i;
	
	for (i = 0; i < numberOfEquations; i++) {
		curVals[i] += steps[i];
	}
}
/** Prints a mathematica point*/
void printMathematicaPoint(double curVals[]) {
	printf("{%lf, %lf},\n", curVals[0], curVals[1]);
}

/** Prints out the current approximation*/
void printCurApprox(double curVals[], int totalVals) {
	int i;
	
	for (i = 0; i < totalVals; i++) {
		printf("X%d: %.5lf ", i, curVals[i]);
	}
	
	printf("\n");
}

int solve(ZeroSystem *sys, double solns[], int max_iterations) {
	
	int i;
	
	double *linearSolns  = malloc(sizeof(double) * sys->numberOfEqs);
	
	// TODO: check each solution against converged delta
	
	for (i = 0; i < max_iterations; i++) {
		// setup linear system with jacobian and then solve it
		SS_Matrix *jacobian = evaluateJacobian(solns, sys);
		
		SS_Matrix *functions = evaluateEquations(solns, sys);

		
		multiplyEntries(functions, -1.0);
				
		SS_Matrix *linear_system = augment(jacobian, functions);
		
		freeMatrix(jacobian);
		freeMatrix(functions);
		
		solveLinearSystem(linear_system, linearSolns);
		
		free(linear_system);
		
		// now perform the next step of newtons method
		stepByAddingLinearSolutions(solns, linearSolns, sys->numberOfEqs);
		
		// print out our partial results
		printMathematicaPoint(solns);
	}
	
	free(linearSolns);
	return sys->numberOfEqs;
}

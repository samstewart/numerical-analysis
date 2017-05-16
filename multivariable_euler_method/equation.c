#include "equation.h"
#include <stdlib.h>

Equation *newEquation(char solvedFor, int numberOfVars) {
	Equation *eq = malloc(sizeof(Equation));
	eq->solvedFor = solvedFor;
	eq->numberOfVariables = numberOfVars;
	eq->partials = malloc(sizeof(func) * numberOfVars);
	return eq;
};

void freeEquation(Equation *equation) {
	free(equation->partials);
	free(equation);
};

double evalPartial(int partial, double vals[], Equation *eq) {
	return eq->partials[partial](vals);
};

ZeroSystem *newZeroSystem(Equation *equations[], int numberOfEqs, int numberOfVars) {
	ZeroSystem *sys = malloc(sizeof(ZeroSystem));
	sys->numberOfVars = numberOfVars;
	sys->equations = equations;
	sys->numberOfEqs = numberOfEqs;
	
	return sys;
};

// TODO: I'm not certain my memory management is quite right
void freeZeroSystem(ZeroSystem *sys) {
	int i = 0;
	for (i = 0; i < sys->numberOfEqs; i++) {
		freeEquation(sys->equations[i]);
	}
	
	free(sys);
};

SS_Matrix *evaluateJacobian(double values[], ZeroSystem *sys) {
	int i;
	
	// make a new matrix for the jacobian
	SS_Matrix *matrix = newMatrix(sys->numberOfEqs, sys->numberOfVars);
	
	// loop through each of the equations then loop through their partial derivatives
	for (i = 0; i < sys->numberOfEqs; i++) {
		int j;
		
		// now evaluate each partial
		for (j = 0; j < sys->equations[j]->numberOfVariables; j++) {
			// put the entry of the partial into the matrix
			setAt(matrix, i, j, evalPartial(j, values, sys->equations[i]));	
		}
	}
	
	return matrix;
};

SS_Matrix *evaluateEquations(double values[], ZeroSystem *sys) {
	int i;
	
	SS_Matrix *matrix = newMatrix(sys->numberOfEqs, 1);
	
	for (i = 0; i < sys->numberOfEqs; i++) {
		// evaluate the appropriate equation
		setAt(matrix, i, 0, sys->equations[i]->evaluate(values));
	}
	
	return matrix;
};
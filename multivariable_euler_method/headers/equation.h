#ifndef EQUATION_H
#define EQUATION_H

#include "matrix.h"

/** simple function pointert that takes a list of values and returns the result*/
typedef double (*func)(double[]);

/** Simple structure representing an equation
in terms of a variable.
*/
typedef struct {
	// function pointer to the function that allows us to evaluation this equation
	func evaluate;
	// total number of variables
	int numberOfVariables;
	// the variable this equation is solved for (not needed for Newtons method since it is implicit)
	char solvedFor;
	// array of function pointers to partial derivatives
	func *partials;
	
} Equation;

Equation *newEquation(char solvedFor, int numberOfVars);
void freeEquation(Equation *equation);

/** evaluates a partial at a given set of values*/
double evalPartial(int partial, double vals[], Equation *eq);

/** Represents a system of equations equal to 0*/
typedef struct {
	int numberOfEqs;
	int numberOfVars;
	
	// we want an array of pointers to equations; it makes everything easier
	Equation **equations;
} ZeroSystem;

ZeroSystem *newZeroSystem(Equation *equations[], int numberOfEqs, int numberOfVars);
void freeZeroSystem(ZeroSystem *system);

/** Evaluates the jacobian at the set of values provided for each partial.*/
SS_Matrix *evaluateJacobian(double values[], ZeroSystem *system);

/** fills a nx1 matrix with the result of evaluating the functions at the provided tuples*/
SS_Matrix *evaluateEquations(double values[], ZeroSystem *system);

#endif EQUATION_H
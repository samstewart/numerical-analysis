#ifndef EQUATION_H
#define EQUATION_H


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

#endif EQUATION_H
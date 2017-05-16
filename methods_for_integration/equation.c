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
#ifndef NEWTONS_MULTI_H
#define NEWTONS_MULTI_H
#include "equation.h"
/** 
* Solves a set of nonlinear equations.
* Does Newton's method in place on the solns array.
* @return the number of solutions
*/
int solve(ZeroSystem *system, double solns[], int max_iterations);

/** simply adds the step values to each of the current values in place*/
void stepByAddingLinearSolutions(double curVals[], double steps[], int numberOfEquations);

/** Prints out the current approximation*/
void printCurApprox(double curVals[], int totalVals);

void printMathematicaPoint(double curVals[]);

////////////// Useful internal functions and partial derivatives //////
///////////////////////////////////////////////////////////////////////
// TODO: talk to Colin about REU
double partial_fx(double vars[]);
double partial_fy(double vars[]);
double partial_gx(double vars[]);
double partial_gy(double vars[]);
double func_f(double vars[]);
double func_g(double vars[]);

#endif
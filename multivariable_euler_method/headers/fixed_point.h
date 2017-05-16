#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include "equation.h"

/** 
Simple method to solve a system using fixed point iterations.
Returns -1 if we did not converge, otherwise it returns the number of solutions.
*/
int solveFP(ZeroSystem *system, double solns[], int iterations);

/**
Solves a system using fixed point iteration but guesses at special constants
for each function to ensure a convergent solution.
*/
int solveFPGuessConstants(ZeroSystem *system, double solns[], int iterations);

/** Check to see if we have converged*/
int didConverge(double curSolns[], double oldSolns[], int numSolns);

/** Real original y function*/
double orig_y_func(double vars[]);

/** Real original x function*/
double orig_x_func(double vars[]);

/** Function that we are evaluating solved in terms of x*/
double x_func(double vars[]);

/** other function that we are evaluating solved in terms of y*/
double y_func(double vars[]);

#endif
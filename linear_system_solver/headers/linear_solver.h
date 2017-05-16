#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include "matrix.h"

/** Solves a linear system of equations */
int solveLinearSystem(SS_Matrix *matrix, double *solutions);

/** checks to see if there exists unique solutions using the determinant (deprecated)*/
void checkDeterminant(SS_Matrix *matrix);

#endif
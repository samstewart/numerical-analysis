#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "matrix.h"

/** 
* Finds solutions to the given matrix using backsubstituion (assumes upper trianglular matrix)
* and returns the number of solutions and places the solutions in the solns[] array
* with the lower solutions first.
*/
int backSubstituteSolutions(SS_Matrix *matrix, double solns[]);

/** 
* Finds solutions to the given matrix (assumes lower trianglular matrix)
* and returns the number of solutions and places the solutions in the solns[] array
* with the lower solutions first.
*/
int forwardSubstituteSolutions(SS_Matrix *matrix, double solns[]);
#endif
#ifndef LU_FACTORER_H
#define LU_FACTORER_
#include "matrix.h"

/**
* Factors the given matrix into two upper and lower triangular matrices
*/
void factorLU(SS_Matrix *matrix, SS_Matrix *lower, SS_Matrix *upper);
	
#endif
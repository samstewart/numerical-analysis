#ifndef SYNTHETIC_DIVISION_H
#define SYNTHETIC_DIVISION_H

#include "polynomial.h"

/** 
Does synthetic division of two polynomials and returns the result. First one must be of degree 1.
Returns the degree of the new polynomial.
If you want to know why this works, you should check out the Khan Academy video.
*/
int syntheticDivide(SS_Polynomial *p1, SS_Polynomial *p2, SS_Polynomial *quotient);

#endif SYNTHETIC_DIVISION_H
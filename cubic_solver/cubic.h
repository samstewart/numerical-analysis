// simple library for finding equations to cubics.
// it returns all three roots by using a combination of complex
// numbers and polynomial long division



#ifndef CUBIC_H
#define 

#import <math.h>
#import <complex.h>

/** 
* We need some structs to store our polynomials
* we represent a cubnic as a series of coefficients
*/
typedef struct {
    double a;
    double b;
    double c;
    double d;
    
} SS_Cubic;
  
 
/**
* Represents a solution to a given cubic.
* We might have real or complex roots.
*/

typedef struct {
    double complex r1;
    double complex r2;
    double complex r3;
} SS_Cubic_Soln;
  
/** Simple function that returns a solution to the given cubic.
* The solution might consist of either real or complex roots
* You should pass in a pointer to a solution.
*/
void ss_solve_cubic(SS_Polynomial cubic, SS_Cubic_Soln *soln);

#endif
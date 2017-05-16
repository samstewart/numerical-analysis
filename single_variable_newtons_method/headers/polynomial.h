#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

/** the type of the polynomial coefficients. Currently, these can be complex numbers */
typedef double _Complex PolyCoeff;

#include <complex.h>

/** simple representation of a polynomial. We represent it using only coefficients.*/
typedef struct {
	// the list of coefficients where the highest coefficient is at the highest index
	// Ask jeff if there is better array synatx?
	PolyCoeff *coefficients;
	
	// the highest power of the polynomial
	int degree;
	
	// the remainder (when doing division)
	PolyCoeff residue;
} SS_Polynomial;

/**
* Creates a new polynomial
* Jeff: how should we do constructors and destructors in C?
*/
SS_Polynomial* newPolynomial(int degree);

/**
* Cleans up an old polynomial
*/
void freePolynomial(SS_Polynomial* poly);

/** 
* Parses coefficients for new polynomial from STDIN.
* Read values into SS_Polynomial.
*/
void parseCoefficients(SS_Polynomial *polynomial);


/** Generates a random coefficient */
PolyCoeff randomPolyCoeff(double max);

/** Simple utility method to display a polynomial*/
void printPolynomial(SS_Polynomial *p);

/**
* Prints out a given polynomial coefficient.
*/ 
void displayPolyCoeff(PolyCoeff x);

#endif
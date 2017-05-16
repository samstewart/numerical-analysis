#include "newtons_guess_methods.h"
#include "synthetic_division.h"
#include <stdlib.h>
#include <stdio.h>

/**
* Makes a new guess based on the old guess. We evaluate the ratio of polynomial to derivative
* at the current guess to derive a new one.
*/
PolyCoeff newtonsGuessStandard(PolyCoeff cur_guess, SS_Polynomial *poly) {
	// find both the derivative and the actual polynomial evaluation at the same time.
	int i = 0;
	
	PolyCoeff derivative = 0;
	PolyCoeff polynomial = 0;
	
	// we accumulate x^n to ensure optimal performance
	PolyCoeff polynomial_x_pow = 1;
	PolyCoeff derivative_x_pow = 1;
	
	// because its the derivative we skip the first constant
	for (i = 0; i < poly->degree + 1; i++ ) {
		
		polynomial += poly->coefficients[i] * polynomial_x_pow;
		
		polynomial_x_pow *= cur_guess;
		
		if (i > 0) {
			// we skip the first constant because it's gone in the derivative
			derivative += i * poly->coefficients[i] * derivative_x_pow;
			
			derivative_x_pow *= cur_guess;
			
		}
		
		
	}
	
	return cur_guess - polynomial / derivative;
}

/** Uses repeated synthetic to evaluate both the polynomial and the underlying derivative.

So two questions:
1. can we do this faster using the recurrence relationship?
2. How do we deal with dividing into a polynomial with a remainder
3. What is a polynomial remainder? */
PolyCoeff newtonsGuessSynthDiv(PolyCoeff cur_guess, SS_Polynomial *poly) {
	SS_Polynomial *monomial_poly = newPolynomial(1);
	
	// we want to eval polynomial and division at cur_guess
	monomial_poly->coefficients[0] = -cur_guess; // we need to negate it because (x - a)
	monomial_poly->coefficients[1] = 1;
	
	// divide the original polynomial by the guess. We are using the Polynomial Remainder Theorem
	SS_Polynomial *reduced_poly = newPolynomial(poly->degree - 1); // knock degree down since dividing by monomial
	
	syntheticDivide(monomial_poly, poly, reduced_poly);
	
	PolyCoeff poly_val = reduced_poly->residue; // by Polynomial Remainder Theorem
	
	// now we divide one more time to get the remainder
	SS_Polynomial *reduced_twice_poly = newPolynomial(reduced_poly->degree - 1);
	
	syntheticDivide(monomial_poly, reduced_poly, reduced_twice_poly);
	
	PolyCoeff derivative_val = reduced_twice_poly->residue; // by polynomial remainder theorem
	
	freePolynomial(reduced_poly);
	reduced_poly = NULL;
	
	freePolynomial(reduced_twice_poly);
	reduced_twice_poly = NULL;
	
	freePolynomial(monomial_poly);
	monomial_poly = NULL;
	
	return cur_guess - poly_val / derivative_val;
};
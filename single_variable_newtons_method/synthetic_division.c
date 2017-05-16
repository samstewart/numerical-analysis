#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "synthetic_division.h"
#include "polynomial.h"
#include <complex.h>

void testSyntheticDivide();

/**
int main(int argv, const char* argc[]) {
	testSyntheticDivide();
	
	return 0;
}
*/

void testSyntheticDivide() {
	SS_Polynomial *p1 = newPolynomial(3);
	
	p1->coefficients[3] = 4 + 2*I;
	p1->coefficients[2] = 7 - 1*I;
	p1->coefficients[1] = 5 + 0*I;
	p1->coefficients[0] = 6 + 5*I;
	
	
	SS_Polynomial *mono = newPolynomial(1);
	mono->coefficients[0] = -(3 - 1*I);
	mono->coefficients[1] = 1;
	
	SS_Polynomial *r1 = newPolynomial(2);
	
	syntheticDivide(mono, p1, r1);
	
	printf("Remainder: ");
	displayPolyCoeff(r1->residue);
	
	SS_Polynomial *r2 = newPolynomial(1);
	
	syntheticDivide(mono, r1, r2);
	
	printf("Remainder: ");
	displayPolyCoeff(r2->residue);
};


int syntheticDivide(SS_Polynomial *p1, SS_Polynomial *p2, SS_Polynomial *quotient) {
	// the divisor has to be a monomial
	if (p1->degree != 1) {
		return -1;
	}

	// now we actually run the algorithm for synthetic division
	quotient->degree = p2->degree - 1; // reduce by one because of monomial division

	// now we loop through the coefficients (from highest to lowest)
	int i;

	// we grab the constant at the end of p1 since it is a monomial.
	// we negate it so that synthetic division works (we want to be able to add at each step)
	PolyCoeff divisor_constant = -(p1->coefficients[0]);

	// the current sum we will multiply divisor_constant by.
	// we start at the highest coefficient.
	PolyCoeff cur_sum = p2->coefficients[p2->degree];

	// "bring down" the first coefficient to first coefficient of quotient
	quotient->coefficients[p2->degree - 1] = cur_sum;

	// we only go to 1 in the p2 coefficients because we want to handle the remainder separately
	// and we start at degree - 1 since we already brought down the first coefficient
	for (i = p2->degree - 1; i >= 1; i--) {
		quotient->coefficients[i - 1] = cur_sum * divisor_constant + p2->coefficients[i];
	
		// we have effectively 'brought down' the other coefficient
		cur_sum = quotient->coefficients[i - 1];
	}

	// take the last summation result and add it as the remainder
	quotient->residue = cur_sum * divisor_constant + p2->coefficients[0];

	return quotient->degree;
}
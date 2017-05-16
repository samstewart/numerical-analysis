/**
* Program that uses newton's method to find roots to a given polynomial.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "polynomial.h"
#include "complex_utility.h"
#include "synthetic_division.h"
#include "newtons_guess_methods.h"
#include <complex.h>

// the number of iterations to run newtons method
const double STABLE_DELTA = .000125;

/** makes a new guess based on the given polynomial coefficient */
PolyCoeff newtonsGuess(PolyCoeff cur_guess, SS_Polynomial *poly);

void displayRoots(PolyCoeff roots[], int total_roots);

int findRoots(SS_Polynomial *poly, PolyCoeff** roots, PolyCoeff guess);

PolyCoeff findRoot(SS_Polynomial *poly, PolyCoeff guess);

int main(int argv, const char* argc[]) {
   	
	printf("-------------------\n");
	// make a new polynomial we wish to fill
	
	// Jeff: where should we put the star?
	// we don't use the constructor because we don't know the degree yet.
	SS_Polynomial *polynomial = (SS_Polynomial *) malloc(sizeof(SS_Polynomial));
	
	// now read in individual coefficients
	parseCoefficients(polynomial);
	
	if (polynomial->degree == 0) {
		printf("Please, you insult me.\n");
		exit(1);
	}
	
	// number of iterations for newton's method
	const PolyCoeff guess = 5.0 + 4*I;
    
	// no perform newtons method
	
	PolyCoeff *roots;
	
	int total_roots = findRoots(polynomial, &roots, guess);

	printf("Total roots: %d\n", total_roots);
	displayRoots(roots, total_roots);
	
	// Jeff: is there a better way to free constituent data parts?
	freePolynomial(polynomial);
	polynomial = NULL;
	
	free(roots);
	roots = NULL;
	
	printf("-------------------\n\n");
		
	return 0;
}



/**
* Displays the resulting roots
*/

void displayRoots(PolyCoeff roots[], int total_roots) {
	printf("Roots:\n===========\n");
	
	int i;
	
	for (i = 0; i < total_roots; i++) {
		displayPolyCoeff(roots[i]);
	}
	
	printf("===========\n");
}

/**
* Runs newtons method for a fixed number of iterations and attempts to find all the roots.
* It returns the total number of roots found and places them in the roots array.
* Is this pattern common where I return the number of the data filled into the array?
*/
int findRoots(SS_Polynomial *poly, PolyCoeff** roots, PolyCoeff guess) {
	
	if (poly->degree == 0) {
		return 0;
	}
		
	
	// allocate an array a bit bigger than the total number of roots (we pad with +5 just in case)
	PolyCoeff *found_roots = malloc(sizeof(PolyCoeff) * (poly->degree + 5));
	
	int total_roots = 0;
	
	PolyCoeff cur_guess = guess;
	
	SS_Polynomial *cur_poly = poly;
	
	// the monomial factor we use for reducing the polynomial
	SS_Polynomial *monomial_divide = newPolynomial(1);
	
	// highest coefficient should always be 1.
	monomial_divide->coefficients[1] = 1;
	
	// is this condition true or could we have additional roots?
	while (total_roots < poly->degree) {
		
		// now if we just reduced to a monomial, we know it is a root, so we're done.
		// would this happen automatically? I don't think so.
		if (cur_poly->degree == 1) {
			found_roots[total_roots] = -cur_poly->coefficients[0] / cur_poly->coefficients[1];
			
			// we need to update the total number of roots afterwards to avoid frencepost
			total_roots++;
			break;
		}
		
		if (total_roots > 0) {
			// if we have found at least one root, change our guess
			// the max is 10 for both the real and imaginary part
			cur_guess = randomPolyCoeff(10);
		}
		
		// find a root
		PolyCoeff root = findRoot(cur_poly, cur_guess);
		
		found_roots[total_roots] = root;
		
		// set the root as the 
		// we need to negate this according to the polynomial factor theorem.
		monomial_divide->coefficients[0] = -root;
		
		// we create a new polynomial with a degree -1 since we are dividing by a monomial
		SS_Polynomial *reduced_poly = newPolynomial(cur_poly->degree - 1);
		
		// divide that root out of the polynomial and thus reduce the polynomial.
		// this function returns a new polynomial.
		syntheticDivide(monomial_divide, cur_poly, reduced_poly);

		
		// if thisn't the first polynomial we received, we should free the memory
		// because we allocate a new one everything we call syntheticDivide
		if (total_roots > 0) {
			freePolynomial(cur_poly);
			cur_poly = NULL;
		}

		cur_poly = reduced_poly;
		
		total_roots++;
	}
	
	freePolynomial(monomial_divide);
	monomial_divide = NULL;
	
	// pass the resulting roots upward
	*roots = found_roots;
	
	return total_roots;
}

/**
* attempts to find a root given an initial guess
*/
PolyCoeff findRoot(SS_Polynomial *poly, PolyCoeff guess) {
	PolyCoeff cur_guess = guess;
	PolyCoeff prev_guess = INFINITY + 0*I;
	PolyCoeff diff = cabs(cur_guess - prev_guess);
	
	// continue to iterate until the solution stablizes
	while (creal(diff) > STABLE_DELTA || cimag(diff) > STABLE_DELTA) {
		// simple newtons method solver
		prev_guess = cur_guess;
		cur_guess  = newtonsGuessSynthDiv(prev_guess, poly);
		
		
		diff = cabs(cur_guess - prev_guess);
	}
	
	return cur_guess;
}



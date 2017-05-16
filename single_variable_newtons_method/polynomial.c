
#include "polynomial.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

void parseCoefficients(SS_Polynomial *polynomial) {
	printf("Enter the **number of coefficients** of the polynomial followed by its coefficients:\n");
	
	// read in the number of coefficients
	int n;

	scanf("%d", &n);
	
	n = n - 1; // convert to degree of polynomial 
	
	polynomial->degree = n;
	polynomial->coefficients = malloc(sizeof(PolyCoeff) * (n + 1));
		
	int i;

	// we have to read in the cofficient to a double first
	double realCoeff;
	// we start at n because degree is one less
	// we read in big-endian order
	for (i = n; i >= 0; i--) {
		scanf("%lf", &realCoeff);
		
		// now we can convert to complex
		polynomial->coefficients[i] = realCoeff + 0 * I;
	}
}

PolyCoeff randomPolyCoeff(double max) {
	
	srand(time(NULL));
	
	// return a new random complex number using the time() parameter as a seed
	double real = drand48() * max;
	
	double imag = drand48() * max;
	
	return real + imag * I;
}

/**
* Creates a new polynomial
* Jeff: how should we do constructors and destructors in C?
*/
SS_Polynomial* newPolynomial(int degree) {
	SS_Polynomial* poly = malloc(sizeof(SS_Polynomial));
	
	poly->coefficients = malloc(sizeof(SS_Polynomial) * (degree + 1));
	poly->degree = degree;
	poly->residue = 0;
	
	return poly;
}

/**
* Cleans up an old polynomial
*/
void freePolynomial(SS_Polynomial* poly) {
	free(poly->coefficients);
	free(poly);
	poly->coefficients = NULL;
	poly = NULL;
}

void displayPolyCoeff(PolyCoeff x) {
	double real = creal(x);
	double imag = cimag(x);

	if (imag > 0) {
		printf("%lf + %lfi\n", real, imag);
	} else if (imag == 0) {
		printf("%lf\n", real);
	} else {
		printf("%lf - %lfi\n", real, fabs(imag));
	}
}

void printPolynomial(SS_Polynomial *p) {
	int i;
	
	for (i = p->degree; i >= 1; i--) {
		printf("%.2lfX^(%d) + ", creal(p->coefficients[i]), i);
	}
	
	// we don't want to display the x for the constant
	printf("%.2lf ", creal(p->coefficients[0]));	
	
	printf("Remainder: ");
	
	displayPolyCoeff(p->residue);
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
	
double derivative(double x, double *coeff, int n);
double function(double x, double *coeff, int n);
void parseCoefficients(double *coeff, int n);
double runNewtonsMethod(double *coeff, int n, int iterations, double guess);

int main(int argv, const char* argc[]) {
	
    printf("Enter the number of coefficients followed by the coefficients themselves: \n");
    
	// read in the number of coefficients
	int n;

	scanf("%d", &n);

	// create a new array to hold the values
	double *coeff = (double *) malloc(sizeof(double) * n);

	// now read in individual coefficients
    parseCoefficients(coeff, n);

    // number of iterations for newton's method
    const int iterations = 30;
    const double guess = 1.5;
    
    // no perform newtons method
    double solution = runNewtonsMethod(coeff, n, iterations, guess);

	free(coeff);

	printf("Approximate solution: %lf\n", solution);
	
    return 0;
}

/** 
* parses the coefficents from STDIN
*/
void parseCoefficients(double *coeff, int n) {
    int i;
	
	for (i = n - 1; i >= 0; i--) {
		scanf("%lf", &coeff[i]);
	}
}

/**
* Runs newtons method for a given number of iterations on the given 
* polynomial
*/
double runNewtonsMethod(double *coeff, int n, int iterations, double guess) {
    
    double cur_guess = guess;
    
    int i;
	for (i = 0; i < iterations; i++) {
	    // simple newtons method solver
		cur_guess  = cur_guess - function(cur_guess, coeff, n) / derivative(cur_guess, coeff, n);
	}
	
    return cur_guess;
}

/**
* the derivative of the mathematical equation that we wish to solve.
*/
double derivative(double x, double *coeff, int n) {
	// return derivatives
	int i = 0;
	double result = 0;

	// because its the derivative we skip the first constant
	for (i = 1; i < n; i++ ) {
		result += i * coeff[i] * pow(x, i - 1);
	}

	return result;
}

/**
* mathematical equation that we wish to solve.
*/
double function(double x, double *coeff, int n) {
	// loop through coefficients
	int i = 0;
	double result = 0;

	for (i = 0; i < n; i++) {
		result += coeff[i] * pow(x, i);
	}

	return result;
}

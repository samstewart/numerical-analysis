#include <stdio.h>
#include <math.h>
#include <malloc.h>
	
double derivative(double x, double *coeff, int n);
double function(double x, double *coeff, int n);

int main(int argv, const char* argc[]) {
	
	// read in the number of coefficients
	int n;

	scanf("%d", &n);

	// create a new array to hold the values
	double *coeff = (double *)malloc(sizeof(double) * n);

	// now read in coefficients
	int i;
	
	for (i = n - 1; i >= 0; i--) {
		scanf("%lf", &coeff[i]);
	}

	i = 0;

	double cur_guess = 0;
	double prev_guess = 2.0;

	int num_iterations = 100;

	for (i = 0; i < num_iterations; i++) {
		cur_guess  = prev_guess - function(prev_guess, coeff, n) / derivative(prev_guess, coeff, n);
		prev_guess = cur_guess;

	}

	free(coeff);

	printf("Final solution: %lf\n", cur_guess);
}

double derivative(double x, double *coeff, int n) {
	// return derivatives
	int i = 0;
	double result = 0;

	// because its the derivative we skip the first constant
	for (i = 1; i < n; i++ ) {
		result += coeff[i] * pow(x, i - 1);
	}

	return result;
}

double function(double x, double *coeff, int n) {
	// loop through coefficients
	int i = 0;
	double result = 0;

	for (i = 0; i < n; i++) {
		result += coeff[i] * pow(x, i);
	}

	return result;
}

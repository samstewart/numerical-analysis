#include <math.h>
#include <stdio.h>

/**
* Prints the error information given a known root and our approximation
* @param root
*/
void printErrorInfo(double real_root, double cur_guess, double prev_guess) {
	double numerator = (cur_guess - real_root);
	double denominator = pow(prev_guess - real_root, 2);

	double ratio = numerator / denominator;

	printf("%.20lf   %.20lf   %.20lf   %.20lf\n", cur_guess, numerator, denominator, ratio);
}
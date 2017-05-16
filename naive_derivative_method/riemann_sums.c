#include <stdio.h>
#include <stdlib.h>
#include "riemann_sums.h"
#include <math.h>

double f(double x) {
	return exp(x)/x;
}

double d1(double x, double delta) {
	return (f(x + delta) - f(x))/delta;
}

double d2(double x, double delta) {
	return (d1(x + delta, delta) - d1(x, delta))/delta;
}

double d3(double x, double delta) {
	return (d2(x + delta, delta) - d2(x, delta))/delta;
}

double d4(double x, double delta) {
	return (d3(x + delta, delta) - d3(x, delta))/delta;
}

int main(int argc, const char* args[]) {
	
	int i;
	double vals[2];
	
	double x = 2.5;
	double h = .1;
	double curh = h;
	for (i = 1; i <= 10; i++) {
 		curh = curh / 10.0;
		
		printf("%d %e %e\n", i, curh, d1(x, curh));
	}
	
}
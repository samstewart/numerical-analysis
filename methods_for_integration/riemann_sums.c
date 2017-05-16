#include <stdio.h>
#include <stdlib.h>
#include "riemann_sums.h"
#include <math.h>

double test_func(double vals[]) {
	double x = vals[0];
	// bit of a flipped parabola
//	return -pow(x - 1, 2) + 2.0; // should be -4.33 between 3 and 4
//	return sin(x*x); // answer between 0 1 should be about .30
	return 4.0 * pow(x, 3) + -2.3*pow(x, 2) + 6.0*x;
//	return pow(x, 3);
}

int main(int argc, const char* args[]) {
	
	Interval interval;
	
	printf("Please enter the endpoints of the interval followed by the number of terms:\n");
	
	scanf("%lf", &interval.a);
	scanf("%lf", &interval.b);
	
	int num_intervals;
	scanf("%d", &num_intervals);
	
	if (num_intervals % 3 != 0) {
		printf("Must have a multiple of three panels!\n");
		exit(1);
	}

	Equation *eq = newEquation('x', 1);
	eq->evaluate = &test_func;
	
	printf("Approx definite integral (Simpsons three eighths rule): %e\n", riemannApprox(interval, eq, num_intervals, SIMPSONS_THREE_EIGTHS_RULE));
	
	printf("Approx definite integral (left endpoint): %e\n", riemannApprox(interval, eq, num_intervals, RIEMANN_LEFT));

	printf("Approx definite integral (trapezoid): %e\n", riemannApprox(interval, eq, num_intervals, TRAPEZOID_RULE));

	printf("Approx definite integral (center): %e\n", riemannApprox(interval, eq, num_intervals, RIEMANN_CENTER));

	freeEquation(eq);
	
	return 0;
}

double riemannApprox(Interval interval, Equation *func, int num_intervals, RiemannType type) {
	int i = 0;
	
	double sum = 0.0;
	double interval_width = (interval.b - interval.a) / (double) num_intervals;
	double func_params[1];
	
	// Note: we are counting by panels, not endpoints
	for (i = 0; i < num_intervals; i++) {
		switch (type) {
			case RIEMANN_LEFT:
				// use the right interval
				func_params[0] = i * interval_width + interval.a;
				sum += func->evaluate(func_params);
				break;
			
			case RIEMANN_RIGHT:
				func_params[0] = (i + 1) * interval_width + interval.a;
				sum += func->evaluate(func_params);
				break;
			case TRAPEZOID_RULE:
				func_params[0] = i * interval_width + interval.a;
				sum += 1.0 / 2.0 * func->evaluate(func_params);

				func_params[0] = (i + 1) * interval_width + interval.a;
				sum += 1.0 / 2.0 * func->evaluate(func_params);				
				break;
			case SIMPSONS_RULE:
				// we do different things depending on what panel we are looking at			
				
				if (i % 2 == 1) {
					func_params[0] = i * interval_width + interval.a;
					sum += 4.0 / 3.0 * func->evaluate(func_params);
					func_params[0] = (i - 1) * interval_width + interval.a;
					sum += 1.0 / 3.0 * func->evaluate(func_params);

					func_params[0] = (i + 1) * interval_width + interval.a;
					sum += 1.0 / 3.0 * func->evaluate(func_params);
				}
				break;
			case SIMPSONS_THREE_EIGTHS_RULE:
				if (i % 3 == 1) {
					func_params[0] = (i - 1) * interval_width + interval.a;
					sum += 3.0 / 8.0 * func->evaluate(func_params);
					func_params[0] = i * interval_width + interval.a;
					sum += 9.0 / 8.0 * func->evaluate(func_params);
					func_params[0] = (i + 1) * interval_width + interval.a;
					sum += 9.0 / 8.0 * func->evaluate(func_params);
					func_params[0] = (i + 2) * interval_width + interval.a;
					sum += 3.0 / 8.0 * func->evaluate(func_params);
				}
				break;
			case RIEMANN_CENTER:
				func_params[0] = i * interval_width + interval_width / 2.0 + interval.a;
				sum += func->evaluate(func_params);
				break;
		}
	}

	sum *= interval_width; // factored it out to increase speed
	
	return sum;
}

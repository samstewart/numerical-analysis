#ifndef REIMAN_SUMS_H
#define REIMAN_SUMS_H

#include "equation.h"

typedef struct {
	// starting point of the interval
	double a;
	double b;
} Interval;

/** The various types of approximations*/
typedef enum {
	RIEMANN_RIGHT,
	RIEMANN_LEFT,
	RIEMANN_CENTER,
	SIMPSONS_RULE,
	SIMPSONS_THREE_EIGTHS_RULE,
	TRAPEZOID_RULE
} RiemannType;

/** 
* Approximates the definite integral of a given function over a given interval
* @return the approximate 'area' under the curve
*/
double riemannApprox(Interval interval, Equation *func, int num_intervals, RiemannType type);

/** Simple function we are trying to integrate*/
double test_func(double vals[]);

#endif

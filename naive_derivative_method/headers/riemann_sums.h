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
	SIMPSONS_THREE_EIGTHS_RULE
} RiemannType;

/** 
* Approximates the definite integral of a given function over a given interval
* @return the approximate 'area' under the curve
*/
double riemannApprox(Interval interval, Equation *func, int num_intervals, RiemannType type);

double f(double x);

double d1(double x, double delta);

double d2(double x, double delta);

double d3(double x, double delta);

double d4(double x, double delta);

#endif

#ifndef INTERPOLATION_H
#define INTERPOLATION_H

/** Represents a single point*/
typedef struct {
	double x;
	double y;
	double radius;
} Point;

typedef struct {
	Point startP;
	Point endP;
	double A;
	double B;
} CubicCoeff;

/** prints a cubic coefficient for debugging*/
void printCubicCoeff(CubicCoeff co);

/** Solves a system of linear equations to find the coefficients for cubic splines*/
int findSplineCoefficients(Point points[], int num_points, CubicCoeff coeff[]);

/** Plots a cubic spline given a list of coefficients*/
double cubicSpline(CubicCoeff coeff[], int num_coeff, double x);

/** Finds the coefficients for a linear regression line. We should have num_points + 1 coeff (need intercepts)*/
int findLinearCoefficients(Point points[], int num_points, double coeff[], int num_coeff);

/** Evaluates the linear regression line at a particular value of x*/
double linearRegression(double coeff[], double x);

/** Evaluates the fitted curve at a particular value of x*/
double fittedCurve(Point points[], int num_points, double x);

#endif

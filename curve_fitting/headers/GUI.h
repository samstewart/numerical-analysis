#ifndef GUI_H
#define GUI_H

#include "comprehensive_interpolation.h";

typedef int bool;
#define true 1
#define false 0

/** Plot the fitted curve over the interval*/
void plotFittedCurve(Point coeff[], int num_coeff, double a, double b, int n);

/** Plot the linear regression curve*/
void plotLinearRegressionCurve(double a, double b, int n);

/** Plots the fitted cubic spline curve*/
void plotCubicSplineCurve(Point points[], int totalPoints, double a, double b, int n);

/** Plots the list of points*/
void plotPoints(Point points[], int n);

/** Inserts a new point */
void addPoint(Point point);

void drawScreen();

void mouseDown(int x, int y);

void mouseUp(int x, int y);

void mouseMove(int x, int y);
#endif
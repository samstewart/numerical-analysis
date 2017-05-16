#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H



/** Represents a single point*/
typedef struct {
	double x;
	double y;
	double radius;
} Point;

/** represents a differential for one dimension in a space */
typedef double(*differential)(Point point[]);

/** Represents a window for plotting */
typedef struct {
	double xmin;
	double xmax;
	double ymin;
	double ymax;
} PlotWindow;

/** Represents a single diff eq*/
typedef struct {
	differential dy;
	differential dx;
} DiffEq;

/** Plots jeff's first example diff eq but one where x only changes by 1. Should be a tapering sine sort of a thing?*/
void plotFirstExampleSecondOrderDifferential(DiffEq diffeq, double init_dy, double step_size, Point start_point, PlotWindow window);

/** Plots a diff-eq given a starting position and the accuracy between steps */
void plotFirstOrderDiffEq(DiffEq diffeq, double step_size, Point start_point, PlotWindow window);

/** Plots the gravity second order diff-eq given a starting position and starting first derivative */
void plotGravitySecondOrderDiffEq(DiffEq diffeq, Point init_derivatives, Point start_point, double step_size, PlotWindow window);

/** Utility function to translate a point in the cartesian coordinate system to one based
in the lower left hand corner of Jeff's graphics system. Curious as to why he picked the lower left hand
corner and not the upper corner as most 2D systems do...
*/
void convertPointToJeffCoor(Point *point, PlotWindow window);

/** Utility function to translate a point from Jeff's system to the standard cartesian coordinate system*/
void convertPointFromJeffCoor(Point *point, PlotWindow window);

#endif

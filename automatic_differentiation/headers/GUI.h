#ifndef GUI_H
#define GUI_H

/** Represents a single point*/
typedef struct {
	double x;
	double y;
	double radius;
} Point;

typedef int bool;
#define true 1
#define false 0

/** Plot the fitted curve over the interval*/
void plotSplineCurve(Point coeff[], int num_coeff, int n);

/** Plots a segment*/
void plotSegment(Point start, Point middle, Point end, int n);

/** Plots the list of points*/
void plotPoints(Point points[], int n);
	
void drawScreen();

void mouseDown(int x, int y);

void mouseUp(int x, int y);

void mouseMove(int x, int y);
#endif
#include "GUI.h"
#include <math.h>
#include "FPT.h"
#include <stdio.h>


int totalPoints = 0;

// sorted listed of points. Every time we insert a new point we find the appropriate spot in the list
// sorted by x position
Point points[200];

// the index of the point we're dragging.
int draggingPointIndex;
bool isDragging;

int main() {
	
	G_init_graphics(800, 600);
	
	G_register_mouse_move_handler(&mouseMove);
	G_register_mouse_down_handler(&mouseDown);
	G_register_mouse_up_handler(&mouseUp);
	
	// fill screen with black
	G_rgb(0,0,0);
	G_clear();
	
	G_rgb(1,0,0);
	
	G_start_event_loop();
	
	return 0;
}

void plotPoints(Point points[], int n) {
	int i;
	
	for (i = 0; i < n; i++) {
		G_fill_circle(points[i].x, points[i].y, points[i].radius);
	}
}

void addPoint(Point point) {
	int i;
	// find an appropriate spot for this point
	// based on its x position
	int insertIndex = 0;
	
	for (i = 0; i < totalPoints; i++) {
		if (point.x < points[i].x) {
			// shift the list up by one and insert the point
			int j;
			// the one we are replacing
			Point toShift = points[i];
			Point temp;
			
			for (j = i; j < totalPoints; j++) {
				// shift up by one
				temp = points[j + 1];
				points[j + 1] = toShift;
				toShift = temp;
			}
			
			// key that we do this *after* to avoid overwriting
			points[i] = point;
			
			totalPoints++;
			return;
		}
	}
	
	totalPoints++;
	
	// just append to the end of this list	
	points[totalPoints - 1] = point;
}
void mouseDown(int x, int y) {
	// check to see if we intersect an existing point
	int i;
	
	for (i = 0; i < totalPoints; i++) {
		double dist = sqrt(pow(points[i].x - x, 2) + pow(points[i].y - y, 2));
		
		// we've clicked on a point
		if (dist < points[i].radius) {
			isDragging = true;
			draggingPointIndex = i;
			return;
		}
	}
	
	
	// otherwise we add a new point
	Point point;
	point.x = x;
	point.y = y;
	point.radius = 5;
	
	// we might need to sort the list
	addPoint(point);
	
	drawScreen();
}

void mouseUp(int x, int y) {
	isDragging = false;
}

void mouseMove(int x, int y) {
	if (isDragging) {
		points[draggingPointIndex].x = x;
		points[draggingPointIndex].y = y;
		
		drawScreen();
	}
}

void drawScreen() {

	
	G_rgb(0,0,0);
	G_clear();
	
	// fill screen with black
	G_rgb(1,0,0);
	
	plotFittedCurve(points, totalPoints, 0, 800, 100);
	plotLinearRegressionCurve(0, 800, 100);
	plotCubicSplineCurve(points, totalPoints, 0, 800, 150	);
	plotPoints(points, totalPoints);
}

void plotLinearRegressionCurve(double a, double b, int n) {
	G_rgb(0,0,1);
	
	double coeffs[2];
	
	findLinearCoefficients(points, totalPoints, coeffs, 2);
	
	double x1, y1, x2, y2;
	
	x1 = a;
	y1 = linearRegression(coeffs, x1);
	
	x2 = b;
	y2 = linearRegression(coeffs, x2);
	
	G_line(x1, y1, x2, y2);
	
	G_rgb(1,0,0);
}

void plotCubicSplineCurve(Point points[], int totalPoints, double a, double b, int n) {
	G_rgb(0,1,0); // set to green
	
	// start by finding the coefficeints
	int num_coeff = (totalPoints - 1) * 2;
	CubicCoeff *coeffs = malloc(sizeof(CubicCoeff) * num_coeff);
	
	findSplineCoefficients(points, totalPoints, coeffs);
	
	int i;
	
	double interval_width = (b - a) / n;
	
	double x1, y1, x2, y2;
	
	for (i = 0; i < n; i++) {
		x1 = a + interval_width * i;
		y1 = cubicSpline(coeffs, num_coeff, x1);
		
		x2 = a + interval_width * (i + 1);
		y2 = cubicSpline(coeffs, num_coeff, x2);
		
		if (y1 < 0 || y2 < 0) {
			continue; // outside range of points
		}
		
		G_line(x1, y1, x2, y2);
	}
	
	G_rgb(1,0,0);
}

void plotFittedCurve(Point points[], int num_coeff, double a, double b, int n_intervals) {	
	int i;
	
	double interval_width = (b - a) / n_intervals;
	
	double x1, y1, x2, y2;
	
	for (i = 0; i < n_intervals; i++) {
		x1 = a + interval_width * i;
		y1 = fittedCurve(points, num_coeff, x1);
		
		x2 = a + interval_width * (i + 1);
		y2 = fittedCurve(points, num_coeff, x2);
		
		G_line(x1, y1, x2, y2);
	}
}
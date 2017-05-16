#include "GUI.h"
#include <math.h>
#include "FPT.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int totalPoints = 0;

PlotWindow plot_window;


const double STEP_SIZE = .0005;

/** These points are in Jeff's coordinate system*/
Point points[200];

// the main diff eq we are graphing
DiffEq diff_eq;

// the index of the point we're dragging.
int draggingPointIndex;
bool isDragging;

double dy(Point p[]) {
	Point p1 = p[0];
	return p1.x * -p1.y;
}

double dx(Point p[]) {
	return 1;
}

int main() {
	
	// TODO: add nice window for moving around and viewing it.
	
	G_init_graphics(800, 600);
	
	G_register_mouse_move_handler(&mouseMove);
	G_register_mouse_down_handler(&mouseDown);
	G_register_mouse_up_handler(&mouseUp);
	
	// fill screen with black
	G_rgb(0,0,0);
	G_clear();
	
	G_rgb(1,0,0);
	
	diff_eq.dy = &dy;
	diff_eq.dx = &dx;
	
	// plot_window.xmin = 0;
	// plot_window.xmax = 3;
	// plot_window.ymin = 0;
	// plot_window.ymax = 3;
	
	plot_window.xmin = -1;
	plot_window.xmax = 2;
	plot_window.ymin = -1;
	plot_window.ymax = 3;

	makeRandomStartingPoints(30);
	
	drawScreen();
	
	G_start_event_loop();
	
	return 0;
}

void makeRandomStartingPoints(int n) {
	int i;
	
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		points[i].x = ((double) rand() / (double) RAND_MAX) * 800;
		points[i].y = ((double) rand() / (double) RAND_MAX) * 600;
		points[i].radius = 5;
		
		totalPoints++;
	}
}
void plotPoints(Point points[], int n) {
	int i;
	
	for (i = 0; i < n; i++) {
		G_fill_circle(points[i].x, points[i].y, points[i].radius);
	}
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
	
	totalPoints++;
	
	points[totalPoints - 1] = point;
	
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
	
	G_rgb(1,0,0);
	
	// plotDiffEqForStartingPoints(points, totalPoints);
	plotArbitraryDifEq();

	plotPoints(points, totalPoints);
}

void plotArbitraryDifEq() {
	Point start_point;
	start_point.x = 1;
	start_point.y = 0;
	
	Point init_derivatives;
	init_derivatives.x = .02;
	init_derivatives.y = .50;
	
	// plotSecondOrderDiffEq(diff_eq, 0, .003, start_point, plot_window);
	 plotGravitySecondOrderDiffEq(diff_eq, init_derivatives, start_point, .001, plot_window);
	//plotFirstExampleSecondOrderDifferential(diff_eq, 1.0, .01, start_point, plot_window);
}

void plotDiffEqForStartingPoints(Point points[], int totalPoints) {
	int i;
	
	for (i = 0; i < totalPoints; i++) {
		plotFirstOrderDiffEq(diff_eq, STEP_SIZE, points[i], plot_window);
	}
}
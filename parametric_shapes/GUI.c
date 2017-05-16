#include "GUI.h"
#include <math.h>
#include "FPT.h"
#include <stdio.h>


int totalPoints = 0;
Point points[200];
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
	
	// fill screen with black
	G_rgb(1,0,0);

	
	if (totalPoints > 0) {
		plotSplineCurve(points, totalPoints, 20);
		plotPoints(points, totalPoints);	
	}
	
}

void plotSegment(Point start, Point middle, Point end, int n) {
	int i;
	
	double interval_width = 1.0 / n;
	double u1,u2 = 0;
	
	double x1, x2, y1, y2;
	
	// skip by two for each interval
	for (i = 0; i < n; i++) {
		u1 = i * interval_width;
		u2 = (i + 1) * interval_width;
		
		x1 = (1.0 / 2.0 - u1 + 1.0 / 2.0 * u1 * u1) * start.x + (1.0 / 2.0 + u1 - u1*u1) * middle.x + (1.0 / 2.0 * u1*u1) * end.x;
		y1 = (1.0 / 2.0 - u1 + 1.0 / 2.0 * u1 * u1) * start.y + (1.0 / 2.0 + u1 - u1*u1) * middle.y + (1.0 / 2.0 * u1*u1) * end.y;
		
		x2 = (1.0 / 2.0 - u2 + 1.0 / 2.0 * u2 * u2) * start.x + (1.0 / 2.0 + u2 - u2*u2) * middle.x + (1.0 / 2.0 * u2*u2) * end.x;
		y2 = (1.0 / 2.0 - u2 + 1.0 / 2.0 * u2 * u2) * start.y + (1.0 / 2.0 + u2 - u2*u2) * middle.y + (1.0 / 2.0 * u2*u2) * end.y;
	
		
		G_line(x1, y1, x2, y2);
	}
}

void plotSplineCurve(Point points[], int n, int n_intervals) {	
	int i;
	
	for (i = 0; i < n + 1; i++) {
		plotSegment(points[i % n], points[(i + 1) % n], points[(i + 2) % n], n_intervals);
	}
}
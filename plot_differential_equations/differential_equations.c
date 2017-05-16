#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FPT.h"
#include "differential_equations.h"

/** Plots a diff-eq given a starting position and the accuracy between steps. You can pick
* any point on the curve and it will plot both forward and backward
*/
void plotFirstOrderDiffEq(DiffEq diffeq, double step_size, Point start_point, PlotWindow window) {
	const int max_iter = 5000000;
	int i = 0;
	
	// make a copy
	Point transformed_start = start_point;
	convertPointFromJeffCoor(&transformed_start, window);
	
	Point last_point = transformed_start;
	Point cur_point[1];
	cur_point[0]  = transformed_start;
	
	// run in the forward direction
	// we're doing all our plotting in our nice little coordinate system and will do the scaling later when drawing
	while ((cur_point[0].x < window.xmax && cur_point[0].x > window.xmin && cur_point[0].y < window.ymax && cur_point[0].y > window.ymin) && i < max_iter) {
		cur_point[0].x += diffeq.dx(cur_point) * step_size;
		cur_point[0].y += diffeq.dy(cur_point) * step_size;
		
		// translate the current point to Jeff's system.
		convertPointToJeffCoor(&cur_point[0], window);
		convertPointToJeffCoor(&last_point, window);
		
		G_line(last_point.x, last_point.y, cur_point[0].x, cur_point[0].y);
		
		convertPointFromJeffCoor(&cur_point[0], window);
		convertPointFromJeffCoor(&last_point, window);
		
		last_point = cur_point[0];
		i++;
	}
	
	// reset and go the other direction
	last_point = transformed_start;
	cur_point[0]= transformed_start;
	i = 0;
	// run in the backward direction
	// we're doing all our plotting in our nice little coordinate system and will do the scaling later when drawing
	while ((cur_point[0].x < window.xmax && cur_point[0].x > window.xmin && cur_point[0].y < window.ymax && cur_point[0].y > window.ymin) && i < max_iter) {
		last_point = cur_point[0];
		
		cur_point[0].x -= diffeq.dx(cur_point) * step_size;
		cur_point[0].y -= diffeq.dy(cur_point)  * step_size;
		
		// convert to Jeff's coordinate system then back again
		convertPointToJeffCoor(&cur_point[0], window);
		convertPointToJeffCoor(&last_point, window);
		
		G_line(last_point.x, last_point.y, cur_point[0].x, cur_point[0].y);
		
		convertPointFromJeffCoor(&cur_point[0], window);
		convertPointFromJeffCoor(&last_point, window);
		
		i++;
	}
}

void plotGravitySecondOrderDiffEq(DiffEq diffeq, Point init_derivatives, Point start_point, double step_size, PlotWindow window) {
	const int max_iter = 20000;
	
	// currently we do something pretty hacky where we just plot across the screen and don't allow the x-coordinate to change
	Point prev_points[3];
	
	// put in the initial values for the recurrance relation
	prev_points[0] = start_point;
	prev_points[1].x = init_derivatives.x * step_size + start_point.x;
	prev_points[1].y = init_derivatives.y * step_size + start_point.y;
	
	int i = 0;
	// run in the forward direction
	// we're doing all our plotting in our nice little coordinate system and will do the scaling later when drawing
	while (i < max_iter) {
		double denom = pow(pow(prev_points[0].x, 2.0) + pow(prev_points[0].y, 2.0), 3.0/2.0);
		prev_points[2].y = -prev_points[0].y * pow(step_size, 2) / denom;
		prev_points[2].y += 2.0 * prev_points[1].y;
		prev_points[2].y -= prev_points[0].y;
		
		prev_points[2].x = -prev_points[0].x * pow(step_size, 2) / denom;
		prev_points[2].x += 2.0 * prev_points[1].x;
		prev_points[2].x -= prev_points[0].x;
		
		
		// translate the current point to Jeff's system.
		convertPointToJeffCoor(&prev_points[2], window);
		convertPointToJeffCoor(&prev_points[1], window);
		convertPointToJeffCoor(&prev_points[0], window);
		
		G_line(prev_points[0].x, prev_points[0].y, prev_points[1].x, prev_points[1].y);
		
		G_line(prev_points[1].x, prev_points[1].y, prev_points[2].x, prev_points[2].y);
		
		// translate back into our coordinate system
		convertPointFromJeffCoor(&prev_points[2], window);
		convertPointFromJeffCoor(&prev_points[1], window);
		convertPointFromJeffCoor(&prev_points[0], window);
		
		// shift downwards
		prev_points[0] = prev_points[1];
		prev_points[1] = prev_points[2];
		
		i++;
	}

}

void plotFirstExampleSecondOrderDifferential(DiffEq diffeq, double init_dy, double step_size, Point start_point, PlotWindow window) {
	const int max_iter = 200000;
	
	// currently we do something pretty hacky where we just plot across the screen and don't allow the x-coordinate to change
	Point prev_points[3];

	double A = 10.0;// strange constant jeff introduced
	
	// put in the initial values for the recurrance relation
	prev_points[0] = start_point;
	prev_points[1].x = prev_points[0].x + step_size;
	prev_points[1].y = init_dy * step_size + start_point.y;
	
	int i = 0;
	// run in the forward direction
	// we're doing all our plotting in our nice little coordinate system and will do the scaling later when drawing
	while (prev_points[1].x < window.xmax && prev_points[1].x > window.xmin && i < max_iter) {
		
		prev_points[2].x = prev_points[0].x + 2.0 * step_size;
		prev_points[2].y = -4.0 * step_size * prev_points[0].x / (1 + prev_points[0].x * prev_points[0].x);
		prev_points[2].y *= prev_points[1].y - prev_points[0].y;
		prev_points[2].y += 2.0 * prev_points[1].y - prev_points[0].y;
		prev_points[2].y -= (2.0 / (1 + prev_points[0].x * prev_points[0].x) + A * A) * step_size * step_size * prev_points[0].y;
		
		// printf("(%lf, %lf) (%lf, %lf) (%lf, %lf)\n", prev_points[0].x, prev_points[0].y, prev_points[1].x, prev_points[1].y, prev_points[2].x, prev_points[2].y);
		// translate the current point to Jeff's system.
		convertPointToJeffCoor(&prev_points[2], window);
		convertPointToJeffCoor(&prev_points[1], window);
		convertPointToJeffCoor(&prev_points[0], window);
		
		G_line(prev_points[0].x, prev_points[0].y, prev_points[1].x, prev_points[1].y);
		
		G_line(prev_points[1].x, prev_points[1].y, prev_points[2].x, prev_points[2].y);
		
		// translate back into our coordinate system
		convertPointFromJeffCoor(&prev_points[2], window);
		convertPointFromJeffCoor(&prev_points[1], window);
		convertPointFromJeffCoor(&prev_points[0], window);
		
		// shift downwards
		prev_points[0] = prev_points[1];
		prev_points[1] = prev_points[2];
		
		i++;
	}
}

/** Utility function to translate a point from Jeff's system to the standard cartesian coordinate system*/
void convertPointFromJeffCoor(Point *point, PlotWindow window) {
	// TODO: shouldn't be hard coded
	double width = 800.0;
	double height = 600.0;
	
	// do coordinate translate
	// we don't have to scale first since we're already at scale in the jeff coordinate
	point->x -= width /  2.0;
	point->y -= height / 2.0;
	
	double window_width  = window.xmax - window.xmin;
	double window_height = window.ymax - window.ymin;
	
	double xscale = window_width / width;
	double yscale = window_height / height;
	
	point->x *= xscale;
	point->y *= yscale;

	point->x += window.xmin + window_width / 2.0;
	point->y += window.ymin + window_height / 2.0;

}

void convertPointToJeffCoor(Point *point, PlotWindow window) {
	// TODO: shouldn't be hard coded
	double width = 800.0;
	double height = 600.0;
	
	double window_width  = window.xmax - window.xmin;
	double window_height = window.ymax - window.ymin;
	
	// now do coordinate scaling
	double xscale = width / window_width;
	double yscale = height / window_height;

	point->x -= window.xmin + window_width / 2.0;
	point->y -= window.ymin + window_height / 2.0; 

	// we have to scale first to get back to the same scale as the window
	point->x *= xscale;
	point->y *= yscale;
	
	// do coordinate translate
	point->x += width / 2.0;
	point->y += height / 2.0;
	
	
}

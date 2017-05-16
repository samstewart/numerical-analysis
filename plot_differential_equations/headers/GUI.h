#ifndef GUI_H
#define GUI_H

#include "differential_equations.h";

typedef int bool;
#define true 1
#define false 0

/** Blasts some random starting points to the screen */
void makeRandomStartingPoints(int n);

/** Plot the differential equation for the starting points */
void plotDiffEqForStartingPoints(Point points[], int totalPoints);

double dy(Point p[]);

double dx(Point p[]);

/** Plots the list of points*/
void plotPoints(Point points[], int n);

/*Plots some arbitrary diff eq with its own method*/
void plotArbitraryDifEq();

void drawScreen();

void mouseDown(int x, int y);

void mouseUp(int x, int y);

void mouseMove(int x, int y);
#endif
#include "fixed_point.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "newtons_multivariable.h"

#define CONVERGE_DELTA .00000000001


int main(int argc, const char* args[]) {
	printf("Fixed Point Iteration\n");
	
	// put together a system of equations
	// solved for x
	Equation *equationForF = newEquation('x', 2);
	// solved for y
	Equation *equationForG = newEquation('y', 2);
	
	equationForF->evaluate    = &x_func;
	equationForG->evaluate    = &y_func;
	
	Equation *equations[2] = {equationForF, equationForG};
	
	ZeroSystem *sys = newZeroSystem(equations, 2, 2);
	
	// we always add 1 because we need a random constant
	double *solns = malloc(sizeof(double) * (2 + 1));
	
	solveFPGuessConstants(sys, solns, 200);
	
	solns[2] = 1; // don't use any new constant
	
	printf("Plugging back in: {%e, %e}\n", orig_x_func(solns), orig_y_func(solns));
	
	freeZeroSystem(sys);
	free(solns);
	
	return 0;
}


int solveFPGuessConstants(ZeroSystem *sys, double solns[], int iterations) {
	// we guess at the constants about 1,000 times or until we converge
	int constantGuesses = 100;
	int i;
	
	for (i = 0; i < constantGuesses; i++) {
		// set the guesses and the constant guess
		solns[0] = drand48() * 20 - 10; // number between -10 and 10
		solns[1] = drand48() * 20 - 10; // number between -10 and 10
		solns[2] = drand48() * 100 - 100; // number between -100 and 100
		
		printf("Trying with guess (%.5lf, %.5lf) and constant (%.5lf)\n", solns[0], solns[1], solns[2]);
		
		// try solving using fixed point and see if it converges
		int numSolns = solveFP(sys, solns, iterations);
		
		if (numSolns > 0) {
			// we have converged
			printf("Converged to {%.5lf, %.5lf}\n", solns[0], solns[1]);
			return numSolns;
		}
	}
	
}

int solveFP(ZeroSystem *sys, double solns[], int iterations) {
	int i;
	
	// we add a +1 for the random constant field we need to pass in
	double *oldSolns = malloc(sizeof(double) * (sys->numberOfEqs + 1));
	
	for (i = 0; i < iterations; i++) {
		
		// now evaluate each of the functions at solns and modify in place
		int j;
		
		// we need to copy in the old solutions each time around
		// we add the +1 to ensure that we copy the constant guess
		for (j = 0; j < sys->numberOfEqs + 1; j++) {
			oldSolns[j] = solns[j];
		}
		
		for (j = 0; j < sys->numberOfEqs; j++) {
			solns[j]    = sys->equations[j]->evaluate(oldSolns);
			
			printMathematicaPoint(oldSolns);
			
			// check if we converged or not
			if (didConverge(oldSolns, solns, sys->numberOfEqs)) {		
				free(oldSolns);
				return sys->numberOfEqs;
			}
			
		}
		

	}
	
	free(oldSolns);
	printf("Did not converge\n");
	return -1;
}

int didConverge(double curSolns[], double oldSolns[], int numSolns) {
	int i = 0;
	
	int totalConverged = 0;
	for (i = 0; i < numSolns; i++) {
		if (fabs(curSolns[i] - oldSolns[i]) < CONVERGE_DELTA) {
			totalConverged++;
		}
	}
	
	// did they all converge?
	if (totalConverged == numSolns) {
		return 1;
	} else{
		return 0;
	}
}
double orig_x_func(double vars[]) {
	double x 		   = vars[0];
	double y 		   = vars[1];
	return 2.0 * x * cos(x - y) - 1;
}

double orig_y_func(double vars[]) {
	double x 		   = vars[0];
	double y 		   = vars[1];
	return cos(x + y) + 4.0 * sin(x * y);
}

double x_func(double vars[]) {
	double x 		   = vars[0];
	double y 		   = vars[1];
	double const_guess = vars[2]; // unneeded for x
	return 1.0 / (2.0 * cos(x - y));
}

double y_func(double vars[]) {
	double x 		   = vars[0];
	double y 		   = vars[1];
	double const_guess = vars[2]; // our constant that we are guessing at
	return y + cos(x + y) / const_guess + 4.0 * sin(x * y) / const_guess;
}
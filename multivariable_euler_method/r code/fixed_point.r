# simple script for fixed point iteration to test convergence

x_func=function(x, y) {
	1/(2* cos(x - y));
}

y_func=function(x, y, m) {
	y + cos(x + y)/m + 4 * sin(x*y)/m;
}

orig_x <- function(x, y) {
	2*x*cos(x - y) - 1;
};

orig_y <- function(x, y) {
	cos(x + y) + 4*sin(x*y);
};

# finds an equation for y that converges after picking a start guess
# it simply varies the constant as discussed in class
find_constant <- function(m) {
	
	max_iters <- 1000 # search around for 1k times
	
	for (i in 1:max_iters) {
		# pick a random constant
		guesses <- runif(2, min=-10, max=10);
		
		if (test_converge(x_func, y_func, m, 100, guesses[1], guesses[2])) {
			cat("Converged with M: ", m, " and initial guess: (", guesses[1], ", ", guesses[2], ")\n");
			return(1);
		}	
	}

	return(0);
}

# see which constants give convergence
test_constants <- function() {
	converge_time <- c()
	for (m in 1:100) {
		
		# now try this constant
	}
}

test_converge <- function(x.func, y.func, y.const, max.trials, x.guess, y.guess) {
	
	# can we do this with something other than a loop? the whole process is basically iterator
	cat("Guess X: ", x.guess, " Guess Y: ", y.guess, " with M:", y.const, "\n\n");
	
	converge_delta <- .00000000001
	
	new <- c(x.guess, y.guess);
	old <- c(Inf, Inf);
	
	converged <- FALSE;
	
	for (i in 1:max.trials) {
		
		if ( abs(old[1] - new[1]) < converge_delta && abs(old[2] - new[2]) < converge_delta) {
			# stupidly redudent but I just want to hack something together
			converged <- TRUE; 
			break;
		}
		
		old <- new;
		new <- c(x.func(old[1], old[2]), y.func(old[1], old[2], y.const));
		
	}
	
	cat("Soln: {", old[1], ", ", old[2], "}, \n");
	cat("Plugin: ", orig_x(old[1], old[2]), ", ", orig_y(old[1], old[2]), "\n");
	
	# return whether or not we converged
	converged;	
}

find_constant();



all_x_func <- list(
c(
eq=1,
func=function(x, y) {
	1/(2 * cos(x - y));
}),

c(
eq=2,
func=function(x, y) {
	asin( - cos( x + y )/4)/y;
}),

c(
eq=1,
func=function(x, y) {
	y + acos(1/(2*x));
}),
c(
eq=1,
func=function(x, y) {
	y + acos(1/(2*x));
})
);

all_y_func <- list(

c(
eq=2,
func=function(x, y) {
	acos(-4 * sin(x*y));
}),

c(
eq=2,
func=function(x, y) {
	asin(cos(x + y) / -4)/x;
}
),

c(
eq=1,
func=function(x, y) {
	x - acos(1/(2*x));
})

);

test_all_combos <- function() {
	for (x_func in all_x_func) {
		for (y_func in all_y_func) {
			if (x_func$eq != y_func$eq) {
				cat("--------------------\n");
			
				print(x_func);
				print(y_func);
				test_converge(x_func$func, y_func$func, 100, FALSE);	
			}	
		}
	}	
}

#test_all_combos();

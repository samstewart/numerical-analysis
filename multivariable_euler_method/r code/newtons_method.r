# simple script to prototype euler-method for non-linear systems
d_fx <- function(x, y) {
	2*cos(x - y) - 2*x*sin(x - y);
	#2*x
	#18*x
}

d_fy <- function(x, y) {
	2*x*sin(x - y);
	#8*y
	# 2.0*x*(-cos(y)*sin(x) - cos(x)*sin(y))
	#8*y
}

d_gx <- function(x, y) {
	4*y*cos(x*y) - sin(x + y);
	#28*x
	#4.0 * y * cos(x*y) - cos(y)* sin(x) + cos(x)*sin(y)
	#3
}

d_gy <- function(x, y) {
	4*x*cos(x*y) - sin(x + y);
	#-18
	#2
}

f <- function(x, y) {
	2*x*cos(x - y) - 1;
	#x^2 + 4*y^2 - 9
	#-1.0 + 2.0*x*(cos(x)*cos(y) - sin(x)*sin(y))
#	-36 + 9*x^2 + 4*y^2
}

g <- function(x, y) {
	cos(x + y) + 4*sin(x*y);
	#14*x^2 - 18*y - 45
	# cos(x)*cos(y) + sin(x)*sin(y) + 4.0*sin(x*y)
#	-6 + 3*x + 2*y;
}
iterations <- 100

x_n <- 2
y_n <- -1
cat("ListPlot[{\n")
for (i in 1:iterations) {
	cat("{", x_n, ",", y_n, "},\n");
	m <- matrix(nrow = 2, ncol = 2);
	
	m[1, 1] <- d_fx(x_n, y_n);
	m[1, 2] <- d_fy(x_n, y_n);
	
	m[2, 1] <- d_gx(x_n, y_n);
	m[2, 2] <- d_gy(x_n, y_n);
	
	b <- c(-f(x_n, y_n), -g(x_n, y_n));
			
	uv <- solve(m, b);
	
	x_n <- x_n + uv[1];
	y_n <- y_n + uv[2];

}
cat("\n}];\n");

cat("Plugging root back in. F: ", f(x_n, y_n), " G: ", g(x_n, y_n), "\n");

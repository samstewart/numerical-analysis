## Simple assignment to use Euler's Method to solve a system of non-linear equations

Note: you have to stop yourself from thinking "I did all the work" because failure means you need to tweak *how* you're working

## The system is two step:
We need a method to iteratively evaluate Newtons method in multiple dimensions along with the ability to solve a linear system of equations. We statically link with our old linear solver.

Helpful guide for using static library: http://codingfreak.blogspot.com/2010/01/creating-and-using-static-libraries-in.html
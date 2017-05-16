#ifndef TAYLOR_DEF
#define TAYLOR_DEF

#include <stdio.h>
#include <math.h>

extern int Tdegree ;


/////////////////////////////////////////////////////////
int copy_T (double *dest, double *source) ;

int make_constant_T(double *t, double v) ;

int make_variable_T(double *t, double v) ;
// essentially makes a linear with value, v

int print_T (char *before, char *control, double *t, char *after) ;

// control is the control string for the doubles
// that will be printed

int scan_T (double *t) ;
/////////////////////////////////////////////////////////
int Add_T (double *r, double *u, double *v) ;
int Sub_T (double *r, double *u, double *v) ;
int Mul_T (double *r, double *u, double *v) ;
int Div_T (double *r, double *u, double *v) ;

int Add_cons_T (double *r, double cons) ;
int Mul_cons_T (double *r, double cons) ;

/////////////////////////////////////////////////////////
int exp_T (double *r,  double *u) ;
int ln_T  (double *r,  double *u) ;

int cossin_T (double *c, double *s, double *u) ;
// c = cos(u) , s = sin(u)

int cos_T (double *r, double *u) ;
int sin_T (double *r, double *u) ;
int tan_T (double *r, double *u) ;

int sqrt_T (double *r, double *u) ;
int cbrt_T (double *r, double *u) ;

int cpow_T (double *r, double *u, double cpow) ;
// r = u^cpow, where cpow is constant

/////////////////////////////////////////////////////////

#endif

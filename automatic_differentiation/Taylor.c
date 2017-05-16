#include <Taylor.h>

int Tdegree ;


int copy_T (double *dest, double *source)
{
  int k ;
  for (k = 0 ; k <= Tdegree ; k++) {
	dest[k] = source[k] ;
  }
  return 1 ;
}



int make_constant_T(double *t, double v)
{
  int k ;
  for (k = 0 ; k <= Tdegree ; k++ ) t[k] = 0 ;
  t[0] = v ;
  return 1 ;
}


int make_variable_T(double *t, double v)
// essentially makes a linear with value, v
{
  int k ;
  for (k = 0 ; k <= Tdegree ; k++ ) t[k] = 0 ;

  t[0] = v ;
  t[1] = 1 ;
  return 1 ;
}



int print_T (char *before, char *control, double *t, char *after)
// control is the control string for the doubles
// that will be printed
{
   int k ;

   printf("%s",before) ;
   printf("[") ;
   for (k = 0 ; k <= Tdegree ; k++) {
	   printf(control,t[k]) ;
	   if (k != Tdegree) { printf(",") ;}
   }
   printf("]") ;
   printf("%s",after) ;
   return 1 ;
}


int scan_T (double *t)
{
  int k,i ;
  char s[100] ;
  double x ;

  k = -1 ;
  i = scanf("%s",s) ;// [

  while (1) {
  i = scanf("%lf",&x) ;	 
  t[++k] = x ;

  i = scanf("%s",s) ; // comma or ]
  if (s[0] == ']') break ;
  }

  Tdegree = k ;

}



//////////////////////////////////////////////////////////
// should be safe for any and all of these parameter
// pointers to point to same things


int Add_T (double *r, double *u, double *v)
// r = u + v
{
  int k ;

  for (k = 0 ; k <= Tdegree ; k++ ) {
		r[k] = u[k] + v[k] ;
  }

  return 1 ;
}




int Sub_T (double *r, double *u, double *v)
// r = u - v
{
  int k ;

  for (k = 0 ; k <= Tdegree ; k++ ) {
	  r[k] = u[k] - v[k] ;
  }

  return 1 ;
}



int Mul_T (double *r, double *u, double *v)
// r = u * v
{
  int n,k ;
  double sum ;
  double p[1000] ;

  for ( n = 0 ; n <= Tdegree ; n++ ) {

	 sum = 0.0 ;
	 for ( k = 0 ; k <= n ; k++ ) {
		sum = sum + u[k] * v[n-k] ;
	 }

	 p[n] = sum ;
  }
  
  copy_T (r,p) ;
  return 1 ;

}





int Add_cons_T (double *r, double constant)
// r =	r + constant
{
  r[0] += constant ;
  return 1 ;
}


int Mul_cons_T (double *r, double constant)
// r =	r * constant
{
  int n ;

  for ( n = 0 ; n <= Tdegree ; n++ ) {
	r[n] *= constant ;
  }
  return 1 ;
}

int Div_T (double *r, double *u, double *v)	 {
  	int n,k ;
  	double sum ;
  	double p[1000] ;

	for ( n = 0 ; n <= Tdegree ; n++ ) {

		sum = u[n];
		for ( k = 0 ; k <= n - 1; k++ ) {
			sum -= p[k] * v[n-k] ;
		}
		
		p[n] = sum / v[0];
		
	}

	copy_T (r,p) ;
	return 1 ;
}

int ln_T  (double *r,  double *u) {
	int n,k ;
  	double sum ;
  	double p[1000];
	
	for ( n = 0; n <= Tdegree; n++ ) {
		
		sum = u[n];
		for ( k = 1; k <= n - 1; k++ ) {
			sum -= (k * p[k] * u[n - k]) / n;
		}
		
		if (n == 0) {
			p[0] = log(u[0]);
		} else {
			p[n] = sum / u[0];
		}
	}
	
	copy_T (r, p) ;
	return 1 ;
}

int cossin_T (double *c, double *s, double *u) {
	int n,k ;
  	double sum_cos, sum_sin;
	double p1[1000];
	double p2[1000];
	
	// fill in the base cases
	p1[0] = cos(u[0]);
	p1[1] = -sin(u[0]) * u[1];
	
	p2[0] = sin(u[0]);
	p2[1] = cos(u[0]) * u[1];
	
	for ( n = 2; n <= Tdegree; n++ ) {
		
		sum_cos = 0.0;
		sum_sin = 0.0;
		
		for ( k = 0; k <= n - 1; k++ ) {
			
			sum_sin += u[k + 1] * (k + 1) * p1[n - 1 - k];
			sum_cos -= u[k + 1] * (k + 1) * p2[n - 1 - k];
		}
		
		sum_sin /= n;
		sum_cos /= n;
		
		p1[n] = sum_cos;
		p2[n] = sum_sin;
		
	}
	
	copy_T (c, p1);
	copy_T (s, p2);
	return 1;
}

int cos_T (double *r, double *u) {
	double s[1000]; // throw this away
	cossin_T(r, s, u);
	return 1;
}

int sin_T (double *r, double *u) {
	double c[1000]; // throw this away
	cossin_T(c, r, u);
	return 1;
}

int exp_T (double *r,  double *u) {
  	int n,k ;
  	double sum ;
  	double p[1000];
	
	for ( n = 0; n <= Tdegree; n++ ) {
		
		sum = 0;
		for ( k = 1; k <= n; k++ ) {
			sum += k * p[n - k] * u[k];
		}
		
		if (n == 0) {
			p[0] = exp(u[0]);
		} else {
			p[n] = sum / n;
		}
		
	}
	
	copy_T (r, p) ;
	return 1 ;
}

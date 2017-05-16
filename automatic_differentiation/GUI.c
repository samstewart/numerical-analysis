
#include <Taylor.h>
#include <stdio.h>


int testA()
{
  double x[100],A[100],B[100],C[100] ;

  Tdegree = 20 ;

  make_variable_T (x, 2.5)  ;
  copy_T          (A, x)    ; // A = x
  Mul_cons_T      (A, 2.0)  ; // A = 2x
  exp_T           (A, A)    ; // A = exp(2x)
  Mul_T           (B, x,x)  ; // B = x^2
  Add_cons_T      (B, 1.0)  ; // B = 1 + x^2
  Div_T           (C, A,B)  ; // C = exp(2x) / (1 + x^2)

  print_T("C = ", "%e\n", C, "\n") ;
  printf("The %d Taylor term is %.15e\n",Tdegree, C[Tdegree]) ;
}




int testB()
{
//        ln(x+exp(x)) - 3*exp(sin(x))*cos(x)
// E =   -------------------------------------
//             4 + cos(x + sin(x))
  double x[100],A[100],B[100],C[100], D[100], E[100], F[100] ;

  Tdegree = 10 ;

  make_variable_T (x, 1.68)  ; // x = 1.0;
  exp_T           (A, x)    ; // A = exp(x)
  Add_T			  (A, x, A) ; // A = exp(x) + x
  ln_T			  (A, A)    ; // A = ln(exp(x) + x)
  sin_T           (B, x)      ; // B = sin(x)
exp_T           (B, B)        ; // B = exp(sin(x))
Mul_cons_T      (B, -3.0);     // B = exp(sin(x)) * 3
cos_T           (C, x)        ;//C = cos(x)
Mul_T          (D, B, C)     ; // D = - 3*exp(sin(x))*cos(x)
Add_T          (D, A, D)      ; // D = ln(x+exp(x)) - 3*exp(sin(x))*cos(x)
/////////////////////////////////////////
sin_T           (E, x);       // E = sin(x)
Add_T           (E, E, x);    // E = sin(x) + x
cos_T           (E, E);       // E = cos(x + sin(x))
Add_cons_T      (E, 4.0)   ; // E = 4 + cos(x + sin(x))
Div_T(F, D, E);

  print_T("F = ", "%e\n", F, "\n") ;
  printf("The %d Taylor term is %.15e\n",Tdegree, A[Tdegree]) ;
}

int testC()
{
	double x[100],A[100],B[100],C[100] ;

	Tdegree = 20 ;

	make_variable_T (x, 1.0)  ; // x = 1;
	copy_T          (A, x)    ; // A = x
	cos_T           (B, A)    ; // B = sin(x)

 	print_T("B = ", "%e\n", B, "\n") ;
	// printf("The %d Taylor term is %.15e\n",Tdegree, A[Tdegree]) ;
}



int main()
{
//  printf("\n") ;
//  printf("test A :\n") ;
//  testA() ;
  printf("-------------------------------------------\n") ;
  printf("test B :\n") ;
  testB() ;
//	testC();
  	printf("\n") ;
}






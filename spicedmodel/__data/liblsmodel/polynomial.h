#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#endif
using namespace std;

/***********************************************************************
 * NAME : 	void polynomial(nd,coef,n,x,y)
 * 
 * DESCRIPTION : This function will calculate the result of a polynomial
 * 
 * INPUTS : 
 * 		int		nd		The degree of the polynomial
 * 		double	*coef	Coefficients, length = nd + 1
 * 		int		n		Number of points to evaluate
 * 		float 	*x		Array of points at which to calculate the 
 * 						polynomial
 * 
 * OUTPUTS : 
 * 		double	*y		Result 
 * ********************************************************************/
void polynomial(int nd, double *coef, int n, float *x, double *y);

/***********************************************************************
 * NAME : 	void polynomial(nd,coef,n,x,y)
 * 
 * DESCRIPTION : This function will calculate the result of a polynomial
 * 
 * INPUTS : 
 * 		int		nd		The degree of the polynomial
 * 		float	*coef	Coefficients, length = nd + 1
 * 		int		n		Number of points to evaluate
 * 		float 	*x		Array of points at which to calculate the 
 * 						polynomial
 * 
 * OUTPUTS : 
 * 		float	*y		Result 
 * ********************************************************************/
void polynomial(int nd, float *coef, int n, float *x, float *y);

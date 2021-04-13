#include "polynomial.h"

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
void polynomial(int nd, double *coef, int n, float *x, double *y) {
		
	int i, j;
	for (i=0;i<n;i++) {
		y[i] = coef[0] + coef[1]*x[i];
		for (j=1;j<nd;j++) {
			y[i] += coef[j+1]*pow(x[i],j+1);
		}
	}
	
}
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
void polynomial(int nd, float *coef, int n, float *x, float *y) {
		
	int i, j;
	for (i=0;i<n;i++) {
		y[i] = coef[0] + coef[1]*x[i];
		for (j=1;j<nd;j++) {
			y[i] += coef[j+1]*powf(x[i],j+1);
		}
	}
	
}

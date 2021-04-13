#ifndef __BOXCOX_H__
#define __BOXCOX_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#endif
using namespace std;

/***********************************************************************
 * NAME : 	BoxCox
 * 
 * DESCRIPTION : 	Box-Cox transforms data.
 * 
 * INPUTS : 
 * 		int 	n		The number of elements
 * 		float 	*x		The input array to be transformed
 * 		float 	lambda	The power of the transform
 * 		float 	shift	The shift applied to x
 * 		float 	mu		Mean value to transform by
 * 		float 	sig		Standard deviation
 * 		
 * OUTPUTS :
 * 		float 	*xt		Transformed array
 * 
 * ********************************************************************/
void BoxCox(int n, float *x, float lambda, float shift, float mu, float sig, float *xt);

/***********************************************************************
 * NAME : 	float BoxCox(x,lambda,shift,mu,sig)
 * 
 * DESCRIPTION : 	Box-Cox transforms data.
 * 
 * INPUTS : 
 * 		float 	x		The input value to be transformed
 * 		float 	lambda	The power of the transform
 * 		float 	shift	The shift applied to x
 * 		float 	mu		Mean value to transform by
 * 		float 	sig		Standard deviation
 * 		
 * RETURNS :
 * 		float 	*xt		Transformed value
 * 
 * ********************************************************************/
float BoxCox(float x, float lambda, float shift, float mu, float sig);


/***********************************************************************
 * NAME :  void ReverseBoxCox(n,xt,lambda,shift,mu,sig,x)
 * 
 * DESCRIPTION : 	Reverses the Box-Cox transform on data.
 * 
 * INPUTS : 
 * 		int 	n		The number of elements
 * 		float 	*xt		The input array to be transformed back
 * 		float 	lambda	The power of the transform
 * 		float 	shift	The shift applied to x
 * 		float 	mu		Mean value to transform by
 * 		float 	sig		Standard deviation
 * 		
 * OUTPUTS :
 * 		float 	*x		Transformed array
 * 
 * ********************************************************************/
void ReverseBoxCox(int n, float *xt, float lambda, float shift, float mu, float sig, float *x);

/***********************************************************************
 * NAME :  float ReverseBoxCox(xt,lambda,shift,mu,sig)
 * 
 * DESCRIPTION : 	Reverses the Box-Cox transform on data.
 * 
 * INPUTS : 
 * 		float 	xt		The input value to be transformed back
 * 		float 	lambda	The power of the transform
 * 		float 	shift	The shift applied to x
 * 		float 	mu		Mean value to transform by
 * 		float 	sig		Standard deviation
 * 		
 * RETURNS :
 * 		float 	x		Reverse-transformed value.
 * 
 * ********************************************************************/
float ReverseBoxCox(float xt, float lambda, float shift, float mu, float sig);

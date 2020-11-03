#include "boxcox.h"

/***********************************************************************
 * NAME : 	void BoxCox(n,x,lambda,shift,mu,sig,xt)
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
void BoxCox(int n, float *x, float lambda, float shift, float mu, float sig, float *xt) {
	
	/* firstly, shift the data */
	int i;
	for (i=0;i<n;i++) {
		xt[i] = x[i] + shift;
	}
	
	/* now do the transform  */
	for (i=0;i<n;i++) {
		xt[i] = (powf(xt[i],lambda) - 1.0)/lambda;
	}
	
	/* normalize if mu != 0 and sig != 1.0 */
	if ((mu != 0.0) & (sig != 1.0)) {
		for (i=0;i<n;i++) {
			xt[i] = (xt[i] - mu)/sig;
		}
	}
	
}

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
float BoxCox(float x, float lambda, float shift, float mu, float sig) {
	float xt = x + shift;
	xt = (powf(xt,lambda) - 1.0)/lambda;
	xt = (xt - mu)/sig;
	return xt;
}

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
void ReverseBoxCox(int n, float *xt, float lambda, float shift, float mu, float sig, float *x) {
	
	/* denormalize if mu != 0 and sig != 1.0 */
	int i;
	if ((mu != 0.0) & (sig != 1.0)) {
		for (i=0;i<n;i++) {
			x[i] = xt[i]*sig + mu;
		}
	} else {
		for (i=0;i<n;i++) {
			x[i] = xt[i];
		}
	}

	/* now do the transform  */
	for (i=0;i<n;i++) {
		x[i] = powf((x[i]*lambda + 1.0),1.0/lambda);
	}

	/* lastly shift the data */
	
	for (i=0;i<n;i++) {
		x[i] = x[i] - shift;
	}

}

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
float ReverseBoxCox(float xt, float lambda, float shift, float mu, float sig) {
	float x = xt*sig + mu;
	x = powf(x*lambda + 1.0,1.0/lambda) - shift;
	return x;
}

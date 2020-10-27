#include "softmax.h"

/***********************************************************************
 * NAME : 	void softmax(z,sm)
 * 
 * DESCRIPTION : Calcualtes the softmax function for the last layer of
 * 					a neural network.
 * 
 * INPUTS : 	
 * 		Matrix	z	The output of the final neural network layer before
 * 					any activation function has been applied to it.
 * 
 * OUTPUTS : 
 * 		Matrix	sm	The softmax function output, effectively a 
 * 					probability.
 * 
 * ********************************************************************/
void softmax(Matrix z, Matrix &sm) {
	
	int i, j, m, k;
	float tot;
	
	/* get the number of samples */
	m = z.shape[0];
	
	/* the number of outputs */
	k = z.shape[1];
	
	/* loop through each one */
	for (i=0;i<n;i++) {
		tot = 0.0;
		/* calculate the total */
		for (j=0;j<k;j++) {
			tot += expf(z.data[i][j]);
		}
		/* now calculate the softmax */
		for (j=0;j<k;j++) {
			sm->data[i][j] = expf(z.data[i][j])/tot;
		}
	}
}
	
	
	

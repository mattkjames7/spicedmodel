#include "reversearray.h"

/***********************************************************************
 * NAME	: 	void reverseArray(n,x)
 * 
 * DESCRIPTION : 	Reverses the elements of an array.
 * 
 * INPUTS : 
 * 		int		n		The number of elements
 * 		float 	*x		The array to be reversed
 * 
 * ********************************************************************/
void reverseArray(int n, float *x) {
	
	float tmp;
	int i;
	for (i=0;i<n/2;i++) {
		tmp = x[i];
		x[i] = x[n-1-i];
		x[n-1-i] = tmp;
	}
}

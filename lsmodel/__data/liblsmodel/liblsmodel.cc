#include "header.h"


void xy2mr(float *x, float *y, int n, float *M, float *R) {
	/*******************************************************************
	 * Convert x and y coordinates to local time and radial distance.
	 * 
	 * ****************************************************************/
	
	int i;
	
	for (i=0;i<n;i++) {
		R[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
		M[i] = fmodf((atan2(-y[i],-x[i])*12.0/M_PI + 24.0),24.0);
	}
}

void polyn(float *x, int n, float *p, int np, float *y) {
	/*******************************************************************
	 * This will sovle a n-order polynomial
	 * 
	 * ****************************************************************/ 
	int i, j;
	for (i=0;i<n;i++) {
		y[j] = 0.0;
		for (j=0;j<np;j++) {
			y[j] += p[j]*powf(x[i],(float) j);
		}
	}
}

void lsvalm(float *M, float *A, float *P, int n, float f, float *out) {
	/*******************************************************************
	 * Calculate the LS variations for a given frequency.
	 * 
	 * ****************************************************************/
	int i;
	float pi2f = 2*M_PI*f;
	
	for(i=0;i<n;i++) {
		out[i] = A[i]*cosf(pi2f*M[i] + P[i]);
	}
}

#include "header.h"

void MavDC(float *R, int n, float a, float b, float c, float d, float *dc) {
	/*******************************************************************
	 * Calculate the DC component of the average ion mass
	 * 
	 * ****************************************************************/
	int i;
	
	for (i=0;i<n;i++) {
		dc[i] = a + b/(1.0 + exp(-c*(R[i] - d)));
	}
}

void MavLS(float *M, float *R, int n, float **ls) {
	/*******************************************************************
	 * Calculate the LS components for average ion mass
	 * 
	 * ****************************************************************/
	
	/* Get the amplitudes and phases */
}

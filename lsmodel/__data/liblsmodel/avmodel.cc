#include "avmodel.h"



/***********************************************************************
 * NAME : void ReadModelParams(ptr)
 * 
 * DESCRIPTION : Read the model parameters from memory.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
void AvModel::ReadModelParams(unsigned char *ptr) {

	/* create a local copy to the pointer */
	unsigned char *p = ptr;

	/* now let's read in the data starting with the DC stuff*/
	p = readArray(p,&dc_,&ndc_);
	
	/* Real components */
	p = readArray(p,&R_,Rshape_);
	
	/* reverse the elements of the array */
	int i,j;
	for (i=0;i<Rshape_[1];i++) {
		reverseArray(Rshape_[1],R_[i]);
	}

	/* Imaginary bits */
	p = readArray(p,&I_,Ishape_);

	/* reverse the elements of the array */
	for (i=0;i<Ishape_[1];i++) {
		reverseArray(Ishape_[1],I_[i]);
	}
}


/***********************************************************************
 * NAME : void PeriodicComponents(n,mlt,R,per)
 * 
 * DESCRIPTION : Converts cartesian x and y to MLT and R
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float 	*mlt	Magnetic local time (in hours)
 * 		float 	*R		R
 * 
 * OUTPUTS : 
 * 		float 	**per	The periodic componensts of the model, shape
 * 						(nm_,n)
 * 
 * 
 * ********************************************************************/
void AvModel::PeriodicComponents(int n, float *mlt, float *R, float **per) {

	/* start by multiplying mlt by 2pi */
	float *m2pi = new float[n];
	int i, j;
	for (i=0;i<n;i++) {
		m2pi[i] = mlt[i]*2*M_PI;
	}
	
	/* work out the real and imaginary components */
	float **real = new float*[nm_];
	float **imag = new float*[nm_];
	for (i=0;i<nm_;i++) {
		/* allocate the memory for each m-number */
		real[i] = new float[n];
		imag[i] = new float[n];
		
		/*call the polynomial functions */
		polynomial(Rshape_[1]-1,R_[i],n,R,real[i]); 
		polynomial(Ishape_[1]-1,I_[i],n,R,imag[i]); 
	}

	/* work out the amplitudes and phases */
	float **A = new float*[nm_];
	float **P = new float*[nm_];
	for (i=0;i<nm_;i++) {
		A[i] = new float[n];
		P[i] = new float[n];
	}

	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			
			A[i][j] = sqrtf(powf(real[i][j],2.0) + powf(imag[i][j],2.0));
			P[i][j] = atan2f(imag[i][j],real[i][j]);
			
		}
	}

	/* now work out the periodic components */
	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			per[i][j] = A[i][j]*cosf(m2pi[j]*wl_[i] + P[i][j]);
		}
	}

	/* clean up */
	delete[] m2pi;
	for (i=0;i<nm_;i++) {
		delete[] A[i];
		delete[] P[i];
		delete[] real[i];
		delete[] imag[i];
	}
	delete[] A;
	delete[] P;
	delete[] real;
	delete[] imag;
	
}

/***********************************************************************
 * NAME : void CartMLTR(n,x,y,mlt,R)
 * 
 * DESCRIPTION : Converts cartesian x and y to MLT and R
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*x		x-coordinate
 * 		float	*y		y-coordinate
 * 
 * OUTPUTS : 
 * 		float 	*mlt	Magnetic local time (in hours)
 * 		float 	*R		R
 * 
 * 
 * ********************************************************************/
void AvModel::CartMLTR(int n, float *x, float *y, float *mlt, float *R) {
	
	int i;
	for (i=0;i<n;i++) {
		R[i] = sqrtf(powf(x[i],2.0) + powf(y[i],2.0));
		mlt[i] = 12.0*atan2f(-y[i],-x[i])/M_PI + 24.0;
		mlt[i] = fmodf(mlt[i],24.0);
	}
}

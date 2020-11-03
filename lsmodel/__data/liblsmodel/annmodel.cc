#include "annmodel.h"

/***********************************************************************
 * NAME : LoadANN(ptr)
 * 
 * DESCRIPTION : Loads the ANN from a memory address.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
void ANNModel::LoadANN(unsigned char *ptr) {

	/* create the NetworkFunc object */
	ann_ = new NetworkFunc(ptr,"softplus","linear","mean_squared");
	
	/* use the ann_ class to work out the maximum m number */
	nm_ = (ann_->s_[ann_->L_-1] - 1)/2;
	
	/* work out the wave lengths */
	int i;
	m_ = new int[nm_];
	wl_ = new float[nm_];

	for (i=1;i<=nm_;i++) {
		m_[i-1] = i;
		wl_[i-1] = ((float) i)/24.0;
	}
}


/***********************************************************************
 * NAME : void ModelComponents(n,mlt,R,S,dc,per)
 * 
 * DESCRIPTION : Converts cartesian x and y to MLT and R
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float 	*mlt	Magnetic local time (in hours)
 * 		float 	*R		R - this need not be scaled as it happens in 
 * 						this function
 *		float 	*S		This is the scaling parameter (SMR or F10.7)
 * 						AFTER it has been transformed.
 * 
 * OUTPUTS : 
 * 		float 	*dc		DC components of the model
 * 		float 	**per	The periodic components of the model, shape
 * 						(nm_,n)
 * 
 * 
 * ********************************************************************/
void ANNModel::ModelComponents(int n, float *mlt, float *R, float *S,
								float *dc, float **per) {

	/* start by multiplying mlt by 2pi */
	float *m2pi = new float[n];
	int i, j;
	for (i=0;i<n;i++) {
		m2pi[i] = mlt[i]*2*M_PI;
	}
	
	/* create an input and output matrix */
	int nf = nm_*2 + 1;
	float **X = new float*[n];
	float **y = new float*[n];
	for (i=0;i<n;i++) {
		X[i] = new float[2];
		X[i][0] = rescaleR(R[i]);
		X[i][1] = S[i];
		y[i] = new float[nf];
	}
	
	/* predict the output */
	ann_->Predict(n,X,y);
	
	
	/* work out the amplitudes and phases */
	float **A = new float*[nm_];
	float **P = new float*[nm_];
	for (i=0;i<nm_;i++) {
		A[i] = new float[n];
		P[i] = new float[n];
	}

	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			
			A[i][j] = sqrtf(powf(y[j][i+1],2.0) + powf(y[j][i+1+nm_],2.0));
			P[i][j] = atan2f(y[j][i+1+nm_],y[j][i+1]);
			
		}
	}

	/* now work out the periodic components and fill dc array*/
	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			per[i][j] = A[i][j]*cosf(m2pi[j]*wl_[i] + P[i][j]);
		}
	}
	for (i=0;i<n;i++) {
		dc[i] = y[i][0];
	}
	

	/* clean up */
	delete[] m2pi;
	for (i=0;i<nm_;i++) {
		delete[] A[i];
		delete[] P[i];
	}
	for (i=0;i<n;i++) {
		delete[] X[i];
		delete[] y[i];
	}
	delete[] X;
	delete[] y;
	delete[] A;
	delete[] P;


	
}


/***********************************************************************
 * NAME : void ModelComponents(n,mlt,R,dc,per)
 * 
 * DESCRIPTION : Calculates the individual model components at a number 
 * 				of Cartisian positions x and y.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*x			SM x-coordinate
 * 		float 	*y			SM y-coordinate
 * 
 * OUTPUTS : 
 * 		float	*dc			The DC component of the model
 * 		float 	**per		The periodic components of the model, shape
 * 							(nm_,n) - where nm_ is the number of 
 * 							m-numbers supported.
 * 
 * 
 * ********************************************************************/
void ANNModel::ModelComponentsCart(int n, float *x, float *y, float *S, 
									float *dc, float **per) {
	
	/* convert x and y to mlt and R */
	float *mlt = new float[n];
	float *R = new float[n];
	CartMLTR(n,x,y,mlt,R);
	
	/* call the model functions */
	ModelComponents(n,mlt,R,S,dc,per);
		
	/* clean up */
	delete [] mlt;
	delete [] R;
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
void ANNModel::CartMLTR(int n, float *x, float *y, float *mlt, float *R) {
	
	int i;
	for (i=0;i<n;i++) {
		R[i] = sqrtf(powf(x[i],2.0) + powf(y[i],2.0));
		mlt[i] = 12.0*atan2f(-y[i],-x[i])/M_PI + 24.0;
		mlt[i] = fmodf(mlt[i],24.0);
	}
}

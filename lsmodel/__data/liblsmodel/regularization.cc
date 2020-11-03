#include "regularization.h"

/***********************************************************************
 * NAME : 	float L1Regularization(w,L1,m)
 * 
 * DESCRIPTION : Calculates the L1 regularization.
 * 
 * INPUTS : 
 * 		MatrixArray	&w	Network weight matrices
 * 		float		L1	L1 regularization parameter
 * 		int			m	Number of samples.
 * 
 * RETURNS : 
 * 		float 	The additional cost due to regularization.
 * 
 * ********************************************************************/
float L1Regularization(MatrixArray &w, float L1, int m) { 
	float J = 0.0;
	
	int i,j,k,nj,nk;
	for (i=0;i<w.n;i++) {
		/*get matrix dimensions*/
		nj = w.matrix[i]->shape[0];
		nk = w.matrix[i]->shape[1];
		for (j=0;j<nj;j++) {
			for (k=0;k<nk;k++) {
				J += fabsf(w.matrix[i]->data[j][k]);
			}
		}
	}
	
	return L1*J/((float) m*2.0);
}


/***********************************************************************
 * NAME : 	float L2Regularization(w,L1,m)
 * 
 * DESCRIPTION : Calculates the L2 regularization.
 * 
 * INPUTS : 
 * 		MatrixArray	&w	Network weight matrices
 * 		float		L2	L2 regularization parameter
 * 		int			m	Number of samples.
 * 
 * RETURNS : 
 * 		float 	The additional cost due to regularization.
 * 
 * ********************************************************************/
float L2Regularization(MatrixArray &w, float L2, int m) { 
	float J = 0.0;
	
	int i,j,k,nj,nk;
	for (i=0;i<w.n;i++) {
		/*get matrix dimensions*/
		nj = w.matrix[i]->shape[0];
		nk = w.matrix[i]->shape[1];
		for (j=0;j<nj;j++) {
			for (k=0;k<nk;k++) {
				J += powf(w.matrix[i]->data[j][k],2.0);
			}
		}
	}
	
	return L2*J/((float) m*2.0);
}

/***********************************************************************
 * NAME : 	ApplyRegGradToMatrix(w,wGrad,L1,L2,m)
 * 
 * DESCRIPTION : Applies regularization to weight gradient matrix.
 * 
 * INPUTS : 
 * 		MatrixArray	&w		The weight matrices.
 * 		MatrixArray	&wGrad	The gradients of the weights from the 
 * 							back-propagation algorithm.
 * 		double		L1		L1 regularization parameter.
 * 		double		L2		L2 regularization parameter.
 * 		int			m		The number of samples.
 * 
 * ********************************************************************/
void ApplyRegGradToMatrix(MatrixArray &w, MatrixArray &wGrad,double L1, double L2, int m) {
	
	int nA = w.n;
	int i, j, ni, nj, k;
	double C1 = L1/(2.0*m), C2 = L2/(2.0*m), l1;
	
	for (k=0;k<nA;k++) {
		ni = w.matrix[k]->shape[0];
		nj = w.matrix[k]->shape[1];
		for (i=0;i<ni;i++) {
			for (j=0;j<nj;j++) {
				if (w.matrix[k]->data[i][j] >= 0) {
					l1 = 1.0;
				} else {
					l1 = -1.0;
				}
				wGrad.matrix[k]->data[i][j] += C1*l1 + C2*w.matrix[k]->data[i][j];
			}
		}
	}
	
}
	


#include "costfunction.h"

/*******************************************************************
 * NAME : 		double crossEntropyCost(h,y,w,L1,L2)
 * 
 * DESCRIPTION : 	This function will calculate the cross-entropy cost 
 * 					function.
 * 
 * INPUTS :
 * 		Matrix		&h 		Matrix containing the ouputs of the neural 
 * 							network, shape (m,K), where m = number of 
 * 							samples, K = number of output nodes.
 *		Matrix		&y 		Matrix containing the one-hot target values 
 * 							for h, shape (m,K).
 *		MatrixArray	&w	 	MatrixArray object containing network 
 * 							weights.
 * 		double 		L1 		L1 regularization parameter.
 * 		double		L2 		L2 regularization parameter.
 * 
 * RETURNS :
 * 		double	J 	cost (set L1=0.0 and L2=0.0 for classification cost). 
 * 
 ******************************************************************/
double crossEntropyCost(Matrix &h, Matrix &y, MatrixArray &w, double L1, double L2) {

	
	double J = 0.0;
	int m, K;
	m = y.shape[0];
	K = y.shape[1];
	int i, j;
	double lh;
	
	/* calculate classification cost first*/
	for (i=0;i<K;i++) {
		for (j=0;j<m;j++) {
			lh = cliplog(h.data[j][i],1.0e-40);
			J += -y.data[j][i]*lh - (1.0-y.data[j][i])*lh;
		}
	}
	J/=((double) m);
	
	/*Calculate L1 cost*/
	if (L1 > 0.0) {
		J += L1Regularization(w,L1,m);
	}
	
	/*Calculate L2 cost*/
	if (L2 > 0.0) {
		J += L1Regularization(w,L2,m);
	}
	
	return J;
}


/*******************************************************************
 * NAME : 		void crossEntropyDelta(h,y,InvAFGrad,Deltas)
 * 
 * DESCRIPTION : 	This function will calculate the deltas of the 
 * 					network.
 * 
 * INPUTS :
 * 		Matrix		&h 		Matrix containing the ouputs of the neural 
 * 							network, shape (m,K), where m = number of 
 * 							samples, K = number of output nodes.
 *		Matrix		&y 		Matrix containing the one-hot target values 
 * 							for h, shape (m,K).
 *		ActFunc		InvAFGrad	Gradient of the inverse of the activation
 * 								function.
 * 
 * OUTPUTS :
 * 		Matrix	Deltas 	The deltas calculatedfrom the results.
 * 
 ******************************************************************/
void crossEntropyDelta(Matrix &h, Matrix &y, ActFunc InvAFGrad, Matrix &Deltas) {
	/*******************************************************************
	 * Calculate delta for this cost function (easy because it is just
	 * the target subtracted from the result).
	 ******************************************************************/
	
	MatrixSubtract(h,y,false,false,Deltas);
}



/*******************************************************************
 * NAME : 		double meanSquaredCost(h,y,w,L1,L2)
 * 
 * DESCRIPTION : 	This function will calculate the mean-squared cost 
 * 					function.
 * 
 * INPUTS :
 * 		Matrix		&h 		Matrix containing the ouputs of the neural 
 * 							network, shape (m,K), where m = number of 
 * 							samples, K = number of output nodes.
 *		Matrix		&y 		Matrix containing the one-hot target values 
 * 							for h, shape (m,K).
 *		MatrixArray	&w	 	MatrixArray object containing network 
 * 							weights.
 * 		double 		L1 		L1 regularization parameter.
 * 		double		L2 		L2 regularization parameter.
 * 
 * RETURNS :
 * 		double	J 	cost (set L1=0.0 and L2=0.0 for classification cost). 
 * 
 ******************************************************************/
double meanSquaredCost(Matrix &h, Matrix &y, MatrixArray &w, double L1, double L2) {
	
	double J = 0.0;
	int m, K;
	m = y.shape[0];
	K = y.shape[1];
	int i, j;
	
	/* calculate classification cost first*/
	for (i=0;i<K;i++) {
		for (j=0;j<m;j++) {
			J += powf(h.data[j][i]-y.data[j][i],2.0);
		}
	}
	J/=((double) 2*m*K);
	
	/*Calculate L1 cost*/
	if (L1 > 0.0) {
		J += L1Regularization(w,L1,m);
	}
	
	/*Calculate L2 cost*/
	if (L2 > 0.0) {
		J += L1Regularization(w,L2,m);
	}
	
	return J;
}

/*******************************************************************
 * NAME : 		void meanSquaredDelta(h,y,InvAFGrad,Deltas)
 * 
 * DESCRIPTION : 	This function will calculate the deltas of the 
 * 					network.
 * 
 * INPUTS :
 * 		Matrix		&h 		Matrix containing the ouputs of the neural 
 * 							network, shape (m,K), where m = number of 
 * 							samples, K = number of output nodes.
 *		Matrix		&y 		Matrix containing the one-hot target values 
 * 							for h, shape (m,K).
 *		ActFunc		InvAFGrad	Gradient of the inverse of the activation
 * 								function.
 * 
 * OUTPUTS :
 * 		Matrix	Deltas 	The deltas calculatedfrom the results.
 * 
 ******************************************************************/
void meanSquaredDelta(Matrix &h, Matrix &y, ActFunc InvAFGrad, Matrix &Deltas) {
	/*******************************************************************
	 * Calculate delta for this cost function.
	 ******************************************************************/
	MatrixSubtract(h,y,false,false,Deltas);
	/*This Delta calculation requires finding the gradient of the 
	 * inverse of the activation function*/
	ApplyFunctionToMatrix(Deltas,InvAFGrad);
}


#include "backpropagate.h"

/***********************************************************************
 * NAME : 	void BackPropogate(w,b,Deltas,a,y,AFGrad,CFDelta,L1,L2,wGrad,bGrad)
 * 
 * DESCRIPTION :  	Propagates errors backwards through the network in
 * 					order to calculate the gradients required for 
 * 					training weights and biases.
 * 
 * INPUTS : 
 * 		MatrixArray		&w		Weight matrices
 * 		MatrixArray		&b		Bias matrices
 * 		MatrixArray		&Deltas	Deltas calculated by cost functions 
 * 								(these are calcualted in function, the 
 * 								array is provided to save repeatedly 
 * 								recreating the array)
 * 		MatrixArray		&a		The outputs of each layer
 * 		Matrix			y		The network training output
 * 		ActFunc			*AFGrad	Array of functions providing gradients 
 * 								to activation functions.
 * 		CostFuncDelta	*CFDelta	Cost function-specific delta function
 * 		double			L1			L1 regularization parameter
 * 		double			L2 			L2 regularization parameter
 * 
 * OUTPUTS : 
 * 		MatrixArray		&wGrad	Array of weight matrix gradients
 * 		MatrixArray		&bGrad	Array of bias matrix gradients
 * 
 * ********************************************************************/
void BackPropagate(MatrixArray &w, MatrixArray &b, 
	MatrixArray &Deltas, MatrixArray &a, Matrix y, ActFunc *AFGrad, 
	CostFuncDelta CFDelta, double L1, double L2, 
	MatrixArray &wGrad, MatrixArray &bGrad) {
	
	int m = a.matrix[0]->shape[0];
	
	/*create a matrix of ones*/
	Matrix ones(1,m);
	ones.AddScalar(1.0);
	
	/* Find out the number of layers*/
	int L = w.n + 1;
	
	/*loop through each layer backwards, calculating the deltas, then gradients*/
	int i;
	for (i=L-2;i>=0;i--) {
		if (i == L-2) {
			/*This would be the final layer, use CF delta*/
			CFDelta(*a.matrix[L-1],y,AFGrad[L-1],*Deltas.matrix[i]);
		} else {
			/*calculate deltas using previous deltas */
			_BackPropDeltas(*Deltas.matrix[i+1],*w.matrix[i+1],AFGrad[i+1],*a.matrix[i+1],*Deltas.matrix[i]);
		}
		/*calculate weight gradients*/
		MatrixDot(*a.matrix[i],*Deltas.matrix[i],true,false,*wGrad.matrix[i]);
		wGrad.matrix[i]->DivideScalar((double) m);
		ApplyRegGradToMatrix(w,wGrad,L1,L2,m);
		
		/*calculate bias gradients*/
		MatrixDot(ones,*Deltas.matrix[i],false,false,*bGrad.matrix[i]);
		bGrad.matrix[i]->DivideScalar((double) m);
	}
		
	
}

/***********************************************************************
 * NAME : 	void _BackPropDeltas(dlin,w,AFGrad,a,dlout)
 * 
 * DESCRIPTION :  	Propagates errors backwards through the network in
 * 					order to calculate the gradients required for 
 * 					training weights and biases.
 * 
 * INPUTS : 
 * 		Matrix		&dlin	Deltas from layer
 * 		Matrix		&w		Weight matrix
 * 		Matrix		&a		The outputs of this layer
 * 		ActFunc		AFGrad	Gradient of this layers activation function
 * 
 * OUTPUTS : 
 * 		Matrix		&dlout	Next set of deltas further down the matrix 
 * 					(backwards)
 * 
 * ********************************************************************/
void _BackPropDeltas(Matrix &dlin, Matrix &w, ActFunc AFGrad, Matrix &a, Matrix &dlout) {
	MatrixDot(dlin,w,false,true,dlout);
	int i, j, ni, nj;
	ni = dlout.shape[0];
	nj = dlout.shape[1];
	
	for (i=0;i<ni;i++) {
		for (j=0;j<nj;j++) {
			dlout.data[i][j] = dlout.data[i][j]*AFGrad(a.data[i][j]);
		}
	}
	
} 

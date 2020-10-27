#ifndef __BACKPROPAGATE_H__
#define __BACKPROPAGATE_H__
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "matrixmath.h"
#include "matrixarray.h"

#include "activationfunctions.h"
#include "costfunction.h"
using namespace std;

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
	MatrixArray &Deltas, MatrixArray &a, Matrix y, ActFunc *AFgrad, 
	CostFuncDelta *CFDelta, double L1, double L2, 
	MatrixArray &wGrad, MatrixArray &bGrad);

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
void _BackPropDeltas(Matrix &dlin, Matrix &w, ActFunc AFGrad, Matrix &a, Matrix &dlout);
#endif


#ifndef __COSTFUNCTION_H__
#define __COSTFUNCTION_H__
#include <math.h>
#include <stdio.h>
#include "matrixarray.h"
#include "cliplog.h"
#include "regularization.h"
using namespace std;


/*******************************************************************
 * NAME : 		float crossEntropyCost(h,y,w,L1,L2)
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
 * 		float 		L1 		L1 regularization parameter.
 * 		float		L2 		L2 regularization parameter.
 * 
 * RETURNS :
 * 		float	J 	cost (set L1=0.0 and L2=0.0 for classification cost). 
 * 
 ******************************************************************/
float crossEntropyCost(Matrix &h, Matrix &y, MatrixArray &w, float L1, float L2);

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
void crossEntropyDelta(Matrix &h, Matrix &y, ActFunc InvAFGrad, Matrix &Deltas);

/*******************************************************************
 * NAME : 		float meanSquaredCost(h,y,w,L1,L2)
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
 * 		float 		L1 		L1 regularization parameter.
 * 		float		L2 		L2 regularization parameter.
 * 
 * RETURNS :
 * 		float	J 	cost (set L1=0.0 and L2=0.0 for classification cost). 
 * 
 ******************************************************************/
float meanSquaredCost(Matrix &h, Matrix &y, MatrixArray &w, float L1, float L2);

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
void meanSquaredDelta(Matrix &h, Matrix &y, ActFunc InvAFGrad, Matrix &Deltas);

/* these typedefs will be used so that we can switch cost functions */
typedef float (*CostFunc)(Matrix&,Matrix&,MatrixArray&,double, double);
typedef float (*CostFuncDelta)(Matrix&,Matrix&,ActFunc,Matrix&);
#endif

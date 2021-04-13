#ifndef __COSTFUNCTION_H__
#define __COSTFUNCTION_H__
#include <math.h>
#include <stdio.h>
#include "matrixarray.h"
#include "cliplog.h"
#include "regularization.h"
#include "activationfunctions.h"
#include "matrixmath.h"
using namespace std;


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
double crossEntropyCost(Matrix &h, Matrix &y, MatrixArray &w, double L1, double L2);

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
double meanSquaredCost(Matrix &h, Matrix &y, MatrixArray &w, double L1, double L2);

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
typedef double (*CostFunc)(Matrix&,Matrix&,MatrixArray&,double, double);
typedef double (*CostFuncDelta)(Matrix&,Matrix&,ActFunc,Matrix&);
#endif

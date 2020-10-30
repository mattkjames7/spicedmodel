#ifndef __ACTIVATIONFUNCTIONS_H__
#define __ACTIVATIONFUNCTIONS_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string.h>

using namespace std;

/***********************************************************************
 * NAME : 			double AF_LeakyReLU(z)
 * 
 * DESCRIPTION : 	Applies the leaky ReLU function to a value.
 * 
 * ********************************************************************/
double AF_LeakyReLU(double z);

/***********************************************************************
 * NAME : 			double AF_LeakyReLUGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the leaky ReLU function.
 * 
 * ********************************************************************/
double AF_LeakyReLUGradient(double z);

/***********************************************************************
 * NAME : 			double AF_InverseLeakyReLU(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the leaky ReLU function.
 * 
 * ********************************************************************/
double AF_InverseLeakyReLU(double a);

/***********************************************************************
 * NAME : 			double AF_InverseLeakyReLUGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					leaky ReLU function.
 * 
 * ********************************************************************/
double AF_InverseLeakyReLUGradient(double a);

/***********************************************************************
 * NAME : 			double AF_Linear(z)
 * 
 * DESCRIPTION : 	Applies the Linear function to a value.
 * 
 * ********************************************************************/
double AF_Linear(double z);

/***********************************************************************
 * NAME : 			double AF_LinearGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the linear function.
 * 
 * ********************************************************************/
double AF_LinearGradient(double z);

/***********************************************************************
 * NAME : 			double AF_ReLU(z)
 * 
 * DESCRIPTION : 	Applies the ReLU function to a value.
 * 
 * ********************************************************************/
double AF_ReLU(double z);

/***********************************************************************
 * NAME : 			double AF_ReLUGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the ReLU function.
 * 
 * ********************************************************************/
double AF_ReLUGradient(double z);

/***********************************************************************
 * NAME : 			double AF_Sigmoid(z)
 * 
 * DESCRIPTION : 	Applies the Sigmoid function to a value.
 * 
 * ********************************************************************/
double AF_Sigmoid(double z);

/***********************************************************************
 * NAME : 			double AF_SigmoidGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the sigmoid function.
 * 
 * ********************************************************************/
double AF_SigmoidGradient(double z);

/***********************************************************************
 * NAME : 			double AF_InverseSigmoid(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSigmoid(double a);

/***********************************************************************
 * NAME : 			double AF_InverseSigmoidGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSigmoidGradient(double a);

/***********************************************************************
 * NAME : 			double AF_Softplus(z)
 * 
 * DESCRIPTION : 	Applies the softplus function to a value.
 * 
 * ********************************************************************/
double AF_Softplus(double z);

/***********************************************************************
 * NAME : 			double AF_SoftplusGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the softplus function.
 * 
 * ********************************************************************/
double AF_SoftplusGradient(double z);

/***********************************************************************
 * NAME : 			double AF_InverseSigmoid(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSoftplus(double a);

/***********************************************************************
 * NAME : 			double AF_InverseSoftplusGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					softplus function.
 * 
 * ********************************************************************/
double AF_InverseSoftplusGradient(double a);

/***********************************************************************
 * NAME : 			double AF_Tanh(z)
 * 
 * DESCRIPTION : 	Applies the tanh function to a value.
 * 
 * ********************************************************************/
double AF_Tanh(double z);

/***********************************************************************
 * NAME : 			double AF_TanhGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the tanh function.
 * 
 * ********************************************************************/
double AF_TanhGradient(double z);

/***********************************************************************
 * NAME : 			double AF_InverseTanh(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the tanh function.
 * 
 * ********************************************************************/
double AF_InverseTanh(double a);

/***********************************************************************
 * NAME : 			double AF_InverseTanhGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					tanh function.
 * 
 * ********************************************************************/
double AF_InverseTanhGradient(double a);

typedef double (*ActFunc)(double);

/***********************************************************************
 * NAME : 			ActFunc AFFromString(str)
 * 
 * DESCRIPTION : 	Returns a pointer to the activation function which
 * 					matches the input string.
 * 
 * INPUTS :
 * 		const char *str		String naming the type of activation 
 * 							function to use, can be any of the 
 * 							following: 'leaky_relu'|'relu'|'linear'|
 * 							'softplus'|'sigmoid'|'tanh'
 * 
 * RETURNS :
 * 		ActFunc		Pointer to the activation function
 * 
 * ********************************************************************/
ActFunc AFFromString(const char *str);


#endif

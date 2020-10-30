#include "activationfunctions.h"

/***********************************************************************
 * NAME : 			double AF_LeakyReLU(z)
 * 
 * DESCRIPTION : 	Applies the leaky ReLU function to a value.
 * 
 * ********************************************************************/
double AF_LeakyReLU(double z) {
	return z*max((double) (z > 0),0.01);
}

/***********************************************************************
 * NAME : 			double AF_LeakyReLUGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the leaky ReLU function.
 * 
 * ********************************************************************/
double AF_LeakyReLUGradient(double z) {
	return max((double) (z > 0),0.01);
}

/***********************************************************************
 * NAME : 			double AF_InverseLeakyReLU(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the leaky ReLU function.
 * 
 * ********************************************************************/
double AF_InverseLeakyReLU(double a) {
	return a/max((double) (a > 0),0.01);
}

/***********************************************************************
 * NAME : 			double AF_InverseLeakyReLUGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					leaky ReLU function.
 * 
 * ********************************************************************/
double AF_InverseLeakyReLUGradient(double a) {
	return AF_LeakyReLUGradient(AF_InverseLeakyReLU(a));
}

/***********************************************************************
 * NAME : 			double AF_Linear(z)
 * 
 * DESCRIPTION : 	Applies the Linear function to a value.
 * 
 * ********************************************************************/
double AF_Linear(double z) {
	return z;
} 

/***********************************************************************
 * NAME : 			double AF_LinearGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the linear function.
 * 
 * ********************************************************************/
double AF_LinearGradient(double z) {
	return 1.0;
} 

/***********************************************************************
 * NAME : 			double AF_ReLU(z)
 * 
 * DESCRIPTION : 	Applies the ReLU function to a value.
 * 
 * ********************************************************************/
double AF_ReLU(double z) {
	return z*((double) (z > 0));
}

/***********************************************************************
 * NAME : 			double AF_ReLUGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the ReLU function.
 * 
 * ********************************************************************/
double AF_ReLUGradient(double z) {
	return ((double) (z > 0));
}

/***********************************************************************
 * NAME : 			double AF_Sigmoid(z)
 * 
 * DESCRIPTION : 	Applies the Sigmoid function to a value.
 * 
 * ********************************************************************/
double AF_Sigmoid(double z) {
	return 1.0/(1.0 + exp(-z));
}

/***********************************************************************
 * NAME : 			double AF_SigmoidGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the sigmoid function.
 * 
 * ********************************************************************/
double AF_SigmoidGradient(double z) {
	double a = AF_Sigmoid(z);
	return a*(1.0 - a);
}

/***********************************************************************
 * NAME : 			double AF_InverseSigmoid(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSigmoid(double a) {
	return -log(1.0/a - 1.0);
}

/***********************************************************************
 * NAME : 			double AF_InverseSigmoidGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSigmoidGradient(double a) {
	return AF_SigmoidGradient(AF_InverseSigmoid(a));
}

/***********************************************************************
 * NAME : 			double AF_Softplus(z)
 * 
 * DESCRIPTION : 	Applies the softplus function to a value.
 * 
 * ********************************************************************/
double AF_Softplus(double z) { 
	
	if (z > 50.0) {
		return z;
	} else {
		return log(1.0 + exp(z));
	}
}

/***********************************************************************
 * NAME : 			double AF_SoftplusGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the softplus function.
 * 
 * ********************************************************************/
double AF_SoftplusGradient(double z) {
	if (z > 50.0) {
		return 1.0;
	} else {
		return 1.0/(1.0 + exp(-z));
	}
}	

/***********************************************************************
 * NAME : 			double AF_InverseSigmoid(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the sigmoid function.
 * 
 * ********************************************************************/
double AF_InverseSoftplus(double a) {
	return log(exp(a) -1.0);
}

/***********************************************************************
 * NAME : 			double AF_InverseSoftplusGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					softplus function.
 * 
 * ********************************************************************/
double AF_InverseSoftplusGradient(double a) {
	return AF_SoftplusGradient(AF_InverseSoftplus(a));
}

/***********************************************************************
 * NAME : 			double AF_Tanh(z)
 * 
 * DESCRIPTION : 	Applies the tanh function to a value.
 * 
 * ********************************************************************/
double AF_Tanh(double z) {
	return 2.0*AF_Sigmoid(z) - 1.0;
}

/***********************************************************************
 * NAME : 			double AF_TanhGradient(z)
 * 
 * DESCRIPTION : 	Returns the gradient of the tanh function.
 * 
 * ********************************************************************/
double AF_TanhGradient(double z) {
	return 1.0 - pow(AF_Tanh(z),2.0);
}

/***********************************************************************
 * NAME : 			double AF_InverseTanh(z)
 * 
 * DESCRIPTION : 	Calculates the inverse of the tanh function.
 * 
 * ********************************************************************/
double AF_InverseTanh(double a) {
	return log(2.0/(a + 1.0) - 1.0)/(-2.0);
}

/***********************************************************************
 * NAME : 			double AF_InverseTanhGradient(z)
 * 
 * DESCRIPTION : 	Calculates the gradient of the inverse of the 
 * 					tanh function.
 * 
 * ********************************************************************/
double AF_InverseTanhGradient(double a) {
	return AF_TanhGradient(AF_InverseTanh(a));
}

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
ActFunc AFFromString(const char *str) {

	if (strcmp(str,"sigmoid") == 0) {
		/* sigmoid function  */
		return AF_Sigmoid;
	} else if (strcmp(str,"leaky_relu") == 0) {
		/* leaky relu function */
		return AF_LeakyReLU;
	} else if (strcmp(str,"relu") == 0) {
		/* return the relu function */
		return AF_ReLU;
	} else if (strcmp(str,"linear") == 0) {
		/* linear function */
		return AF_Linear;
	} else if (strcmp(str,"softplus") == 0) {
		/* softplus function */
		return AF_Softplus;
	} else if (strcmp(str,"tanh") == 0) {
		/* tanh function */
		return AF_Tanh;
	} else {
		/* if no match then return sigmoid as default */
		return AF_Sigmoid;
	}
}

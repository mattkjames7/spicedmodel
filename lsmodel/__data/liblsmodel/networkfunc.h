#ifndef __NETWORKFUNC_H__
#define __NETWORKFUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixarray.h"
#include "matrixmath.h"
#include "activationfunctions.h"
#include "costfunction.h"
#include "readarray.h"

using namespace std;

/***********************************************************************
 * NAME : NetworkFunc
 * 
 * DESCRIPTION : An untrainable artificial neural network object. The 
 * 				point of this is to load an ANN from memory and use it
 * 				purely for prediction.
 * 
 * ********************************************************************/
class NetworkFunc {
	public:
		/* this object must be loaded from memory address */
		NetworkFunc(unsigned char*, const char*, const char*, const char*);
		
		/*or file*/
		//NetworkFunc(const char*,  const char*, const char*, const char*);
		
		/* or a blank one*/
		NetworkFunc(int, int*, const char*,const char *, const char*);
		
		
		/* copy constructor */
		NetworkFunc(const NetworkFunc &obj);
		
		/*Destructor */
		~NetworkFunc();
		
		/*Predict the output based on an input matrix*/
		void Predict(int, float **, float **);

        /*Weights and biases*/
        MatrixArray *W_, *B_;

		/* number of layers/nodes per layer */
		int L_;
		int *s_;
		
		/* rescaling parameters */
		float *scale0_, *scale1_;
		
	private:

		
		
        /*Activation function lists*/
        int HiddenAFCode_; //integer code corresponding to the type of neuron
        int OutputAFCode_; //integer code corresponding to the type of neuron
        ActFunc *AF_; //Actual activation functions will be stored here

        /*Cost function stuff*/
        CostFunc CF_; //The actual cost function pointer
        

        
        /*store the training and validation costs*/
        int nEpoch_;
        float *Jt_, *Jc_;
        
        /* private functions*/
        
        /* a function to populate the activation functions */
        void _PopulateActivationFunctions(const char *, const char *);
        
        /* another to set the cost function */
        void _SetCostFunction(const char *);
	
		/* A functionw hich creates a matrix array that allows us to
		propagate data through the network */
		MatrixArray* _CreatePropagationMatrices(int);

		/* This function will rescale the output matrix so that produces
		the expected values */
		void _RescaleOut(Matrix &);
};


#endif

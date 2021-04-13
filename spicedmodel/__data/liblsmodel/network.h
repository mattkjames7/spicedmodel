#ifndef __NETWORK_H__
#define __NETWORK_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <random>
#include "matrix.h"
#include "matrixmath.h"
#include "matrixarray.h"
//#include "propagate.h"
#include "costfunction.h"
//#include "predict.h"
//#include "thetagradient.h"
//#include "updatetheta.h"
#include "arraytools.h"
using namespace std;


class Network {
	public:
	
		/* Network object constructors */
		/* Start a new network */
		Network(int,int*,float,float);
		/* load from a stored file */
		Network(const char*);
		/* load from a memory address */
		Network(unsigned char *);
		
		/* Copy constructor */
		Network(const Network &obj);
		
		/* Destructor */
		~Network();
		
		/*Changing network*/
		void ResetWeights();
		void ResetNetwork();
		void ChangeNetworkArchitecture();
		void InsertHiddenLayer();
		void UseBestWeights();	
		
		/* edit the activation functions with an integer code*/
		void SetActivationFunction(int,int);
		
		/* set the training algorithm */
		void SetTrainingAlgorithm(int);
		
		/* set the cost function */
		void SetCostFunction(int);
		
		void SetL1();
		void SetL2();
		
		/*Input data*/
		void InputTrainingData(int*,double*,int,int*,bool);
		void InputCrossValidationData(int*,double*,int,int*,bool);
		void InputTestData(int*,double*,int,int*,bool);
		
		/*Training network*/
		void Train();
		
		/*Classification*/
		void ClassifyData(int*,float*,int,int*);
		void ClassifyData(int*,float*,int,int*,float*);

		/*Save network to file*/
		void Save(const char*);

		/*Return parameters*/
		int GetnSteps();
		void GetTrainingProgress(float*,float*,float*,float*,float*,float*,float*);
		void GetTrainingAccuracy(float*,float*);
		void GetCrossValidationAccuracy(float*,float*);
		void GetTestAccuracy(float*,float*);
		int GetL();
		void Gets(int*);
	private:
		/*Network architecture*/
        int L; //number of layers
        int *s; //number of units in each layer
        bool Trained;
        
        /*Regularization parameters*/
        double L1, L2;
        
        /*Weight matrices*/
        MatrixArray *ThetaW, *ThetaWGrad;
        
        /*Bias matrices*/
        MatrixArray *ThetaB, *ThetaBGrad;
        
        /*Delta matrices - these will hopefully speed up training if they're only created once for each training set*/
        MatrixArray *Delta;
        
        /*Activation function lists*/
        int *AFCodes; //integer code corresponding to the type of neuron
        ActFunc *AF; //Actual activation functions will be stored here
        ActFunc *AFgrad; //These will be used to calculate the gradient during back propagation (and therefore need ot be inverse)

        /*Cost function stuff*/
        int CFcode; //integer corresponding to the type of cost function to use
        CostFunc *CF; //The actual cost function pointer
        CostFuncDelta *CFDelta; //Pointer to the object which calculates the deltas

        /*Training data*/
        Matrix *Xt; //Training data matrix, shape (mt,s[0])
        int *yt0 = NULL; //integer class labels, shape (mt,)
        Matrix *yt; //one-hot matrix, shape (mt,s[-1])
        bool TData; //True if data exists
        int mt; //number of samples
        MatrixArray *at, *zt; //Training set propagation arrays

        /*Cross-validation data*/
        Matrix *Xc; 
        int *yc0 = NULL; 
        Matrix *yc; 
        bool CData; 
        int mc;
        MatrixArray *ac, *zc;

        /*Test data*/
        Matrix *Xtest;
        int *ytest0 = NULL; 
        Matrix *ytest;
        bool TestData; 
        int mtest; 
        MatrixArray *atest, *ztest; 
        
        /*Storing Best Weights (based on CV accuracy)*/
        MatrixArray *BestThetaW, *BestThetaB; //stored best weights
        bool Best; // whether or not the best weights are being stored
        float BestAccuracy; //best CV accuracy saved during training

		/*Training progress arrays*/
		float *Jt, *JtClass, Jc, Jtest; //Cost function
		float *At, *Ac, *Atest; //Percentage classification accuracy  
		int nSteps;

		/*Private functions to write*/
		void _GetOneHotClassLabels(int*,Matrix&);
		void _CreatePropagationMatrices(MatrixArray&,MatrixArray&);
		void _InitDeltaMatrices();
		void _CalculateStepGD();
		void _CalculateStepNesterov();
		void _CalculateStepRMSProp();
		void _CalculateStepRProp();
		void _CheckCostGradient();
		void _PopulateActivationFunctions();
		void _SetCostFunction();
		void _TrainNetwork();
		void _LoadNetwork();
		void _AppendToArray(float*);
		void _InitWeights();
};		
#endif

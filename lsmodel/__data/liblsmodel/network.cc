#include "network.h"
//This constructor will be used to initialize the network
Network::Network(int nLayers, int *Layers, float L1, float L2, bool FT, int *ActFunctions, int CostFunction) {
	/*******************************************************************
	 * This should work in pretty much the same way as the Python object
	 * (PyNet) but hopefully a bit quicker!
	 * 
	 * Inputs:
	 * 		nLayers - Number of layers in the network.
	 * 		*Layers - Integer array of size nLayers denoting how many
	 * 			nodes are in each layer.
	 * 		L1 - L1 regularization parameter.
	 * 		L2 - L2 Regularization parameter.
	 * 		FT - Boolean, if true enables forward thinking (learning one
	 * 			hidden layer at a time during training).
	 * 		*ActFunctions - Array of integers which correspond to
	 * 			the activation functions in each layer except the input 
	 * 			layer. Values are:
	 * 				0 - Linear
	 * 				1 - Sigmoid
	 * 				2 - Tanh
	 * 				3 - ReLU
	 * 				4 - Leaky ReLU
	 * 				5 - Softplus (Smooth ReLU)
	 * 		CostFunction - Integer which tells object which cost 
	 * 			function we should use. Available options are:
	 * 				1 - Cross-entropy
	 * 				2 - Mean squared.
	 * 
	 * 
	 * ****************************************************************/
	int i;
	/*Set the network architecture up*/
	Network::Trained = false;
	Network::L = nLayers;
	Network::s = new int[L];
	for (i=0;i<L;i++) {
		Network::s[i] = Network::Layers[i];
	}
	Network::FT = FT;

	/*set up activation functions*/
	Network::_PopulateActivationFunctions(ActFunctions);
	
	/*set cost function*/
	Network::_SetCostFunction(CostFunction);
	
	/*Store regularization parameters*/
	Network::L1 = L1;
	Network::L2 = L2;
	
	/*Initialize weight and bias matrices*/
	Network::_InitWeights();
	
	
	/*set cost function and accuracy arrays to NULL*/
	Network::Jt = NULL;
	Network::JtClass = NULL;
	Network::Jc = NULL;
	Network::Jtest = NULL;
	Network::At = NULL;
	Network::Ac = NULL;
	Network::Atest = NULL;

	/*initialize some other parameters*/
	Network::nSteps = 0;
	Network::TData = false;
	Network::CData = false;
	Network::TestData = false;
	Network::Trained = false;
	Network::mt = 0;
	Network::mc = 0;
	Network::mtest = 0;
}

Network::Network(const char *fname) {
	FILE *f;
	int Xshape[2];
	int i;
	f = fopen(fname,"rb");
	fread(&Trained,sizeof(bool),1,f);
	fread(&L,sizeof(int),1,f);
	s = new int[L];
	fread(s,sizeof(int),L,f);
	fread(&lambda,sizeof(float),1,f);
	fread(&range,sizeof(float),1,f);
	fread(&mt,sizeof(int),1,f);
	fread(&mcv,sizeof(int),1,f);
	nT = L - 1;
	na = L;
	nz = L - 1;
	Tdims = new int[2*nT];
	adims = new int[2*na];
	zdims = new int[2*nz];
	ddims = new int[2*na];
	TData = false;
	CVData = false;
	if (mt > 0) {
		TData = true;
		Xshape[0] = mt;
		Xshape[1] = s[0]+1;
		Xt = new Matrix(Xshape);
		fread(Xt->data,sizeof(float),Xt->len,f);
		yt = new int[mt];
		fread(yt,sizeof(int),mt,f);
		for (i=0;i<L;i++) {
			ddims[i*2] = mt;
			ddims[i*2 + 1] = s[i];
			if (i > 0) { 
				zdims[i*2 - 2] = mt;
				zdims[i*2 - 1] = s[i];	
			}
			if (i== L-1) {
				adims[i*2] = mt;
				adims[i*2 + 1] = s[i];

			} else {
				adims[i*2] = mt;
				adims[i*2 + 1] = s[i] + 1;
			}
		}
		
		at = new MatrixArray(L,adims);
		zt = new MatrixArray(L-1,zdims);
		delta = new MatrixArray(L,ddims);
		
		at->matrix[0]->FillMatrix(Xt->data);
	}
	if (mcv > 0) {
		CVData = true;
		Xshape[0] = mcv;
		Xshape[1] = s[0]+1;
		Xcv = new Matrix(Xshape);
		fread(Xcv->data,sizeof(float),Xcv->len,f);
		ycv = new int[mcv];
		fread(ycv,sizeof(int),mcv,f);
		int adimscv[L*2], zdimscv[(L-1)*2];
		for (i=0;i<L;i++) {
			if (i > 0) { 
				zdimscv[i*2 - 2] = mcv;
				zdimscv[i*2 - 1] = s[i];	
			}
			if (i== L-1) {
				adimscv[i*2] = mcv;
				adimscv[i*2 + 1] = s[i];

			} else {
				adimscv[i*2] = mcv;
				adimscv[i*2 + 1] = s[i] + 1;
			}
		}
		
		acv = new MatrixArray(L,adimscv);
		zcv = new MatrixArray(L-1,zdimscv);
		acv->matrix[0]->FillMatrix(Xcv->data);		
	}
	

	for (i=0;i<L-1;i++) {
		Tdims[i*2] = s[i + 1];
		Tdims[i*2+1] = s[i] + 1;
	}
	Theta = new MatrixArray(nT,Tdims);	
	dTheta = new MatrixArray(nT,Tdims);
	for (i=0;i<L-1;i++) {
		fread(Theta->matrix[i]->data,sizeof(float),Theta->matrix[i]->len,f);
	}
	fread(&nSteps,sizeof(int),1,f);
	fread(&nJ,sizeof(int),1,f);
	
	Jt = (float*) malloc(nJ*sizeof(float));
	Jcv = (float*) malloc(nJ*sizeof(float));
	Acct = (float*) malloc(nJ*sizeof(float));
	Acccv = (float*) malloc(nJ*sizeof(float));
	
	fread(Jt,sizeof(float),nJ,f);
	fread(Jcv,sizeof(float),nJ,f);
	fread(Acct,sizeof(float),nJ,f);
	fread(Acccv,sizeof(float),nJ,f);
	fclose(f);
}

void Network::_InitWeights() {
	/*initialize the weight and bias matrices*/
	int i, Wshapes[(Network::L-1)*2], Bshapes[(Network::L-1)*2];
	for (i=0;i<Network::L-1;i++) {
		Wshapes[i*2] = Network::s[i];
		Bshapes[i*2] = Network::1;
		Wshapes[i*2+1] = Network::s[i+1];
		Bshapes[i*2+1] = Network::s[i+1];
	}
	Network::ThetaW = new MatrixArray(Network::L-1,Wshapes);
	Network::ThetaWGrad = new MatrixArray(Network::L-1,Wshapes);
	Network::ThetaB = new MatrixArray(Network::L-1,Bshapes);
	Network::ThetaBGrad = new MatrixArray(Network::L-1,Bshapes);
	
	Network::ResetWeights();
}

void Network::ResetWeights() {
	/*initialize the normally-distributed random number generator*/
	default_random_engine generator;
	normal_distribution<double> distribution(0.0,1.0);
	
	/*go through each matrix, scale by 1/sqrt(s[i])*/
	int i, j, k, ni, nj, nk;
	double scale;
	ni = Network::L-1
	for (i=0;i<ni;i++) {
		nj = Network::ThetaW.matrix[i].shape[0]
		nk = Network::ThetaW.matrix[i].shape[1]
		scale = sqrt((double) Network::s[i]);
		for (j=0;j<nj;j++) {
			for (k=0;k<nk;k++) {
				Network::ThetaW.matrix[i].data[j][k] = distribution(generator)/scale;
			}
		}	
		for (k=0;k<nk;k++) {
			Network::ThetaB.matrix[i].data[1][k] = distribution(generator);
		}		
	}	
}

void Network::ResetNetwork() {
	Network::ResetWeights()
	
	if (Network::Trained) {
		DestroyArray(Network::At);
		Network::At = NULL;
		DestroyArray(Network::Ac);
		Network::Ac = NULL;
		DestroyArray(Network::Atest);
		Network::Atest = NULL;
		
		DestroyArray(Network::Jt);
		Network::Jt = NULL;
		DestroyArray(Network::JtClass);
		Network::JtClass = NULL;
		DestroyArray(Network::Jc);
		Network::Jc = NULL;
		DestroyArray(Network::Jtest);
		Network::Jtest = NULL;
		
		Network::nSteps = 0;
		Network::Trained = false;
	}
	
}

Network::ChangeNetworkArchitecture(int newL, int *newS) {
	/*******************************************************************
	 * This will change the architecture of the hidden layers of the 
	 * network, the input and output will remain the same.
	 * 
	 * Inputs:
	 * 		newL - new total number of layers (including in and out)
	 * 		*newS - array containing the full new architecture. NOTE:
	 * 			newS[0] and newS[newL-1] are ignored, they could be 
	 * 			totaly random numbers and it wouldn't make a difference;
	 * 			the inputs and outputs stay exactly the same.
	 * 
	 * ****************************************************************/
	
	/*copy old stuff to a temp array first*/
	int tmpL = Network::L;
	int *tmpS;
	tmpS = CreateArray(tmpS,tmpL);
	CopyArray(Network::s,tmpS,tmpL);
	DestroyArray(Network::s);	
	
	/*redefine new s and L*/
	Network::L = newL;
	Network::s = CreateArray(Netowkr::s,newL);
	CopyArray(newS,Network::s,newL);
	Network::s[0] = tmpS[0];
	Network::s[newL-1] = tmpS[tmpL-1];
	
	/*reset weights*/
	Network::ResetWeights();
	
	/*change propagation arrays*/
	
	/*repopulate activation functions*/
	
	
}

void Network::_PopulateActivationFunctions(int *ActFunctions){
	/*******************************************************************
	 * This procuedure will create a pointer array to the activation
	 * functions used in each layer.
	 * ****************************************************************/
	 Network::AF = new ActFunc[Network::L-1];
	 Network::AFgrad = new ActFunc[Network::L-1];
	 int i;
	 for (i=0;i<Network::L-1;i++) {
		Network::AFCodes[i] = ActivationFunctions[i];
		if (ActivationFunctions[i] == 0) {
			/*linear function*/
			Network::AF[i] = AF_Linear;
			Network::AFgrad[i] = AF_LinearGradient;
		} else if (ActivationFunctions[i] == 1) {
			/*Sigmoid*/
			Network::AF[i] = AF_Sigmoid;
			Network::AFgrad[i] = AF_InverseSigmoidGradient;
		} else if (ActivationFunctions[i] == 2) {
			/*Tanh*/
			Network::AF[i] = AF_Tanh;
			Network::AFgrad[i] = AF_InverseTanhGradient;
		} else if (ActivationFunctions[i] == 3) {
			/*ReLU*/
			Network::AF[i] = AF_ReLU;
			Network::AFgrad[i] = AF_ReLUGradient;
		} else if (ActivationFunctions[i] == 4) {
			/*Leaky ReLU*/
			Network::AF[i] = AF_LeakyReLU;
			Network::AFgrad[i] = AF_InverseLeakyReLUGradient;
		} else if (ActivationFunctions[i] == 5) {
			/*Softplus*/
			Network::AF[i] = AF_Softplus;
			Network::AFgrad[i] = AF_InverseSoftplusGradient;
		}
	}
}

void Network::_SetCostFunction(int CostFunction) {
	Network::CFcode = CostFunction;
	if (CostFunction == 1) {
		/*cross-entropy*/
		Network::CF = CrossEntropyCost;
		Network::CFDelta = CrossEntropyDelta;
	} else if (CostFunction == 2) {
		/*mean-squared*/
		Network::CF = MeanSquaredCost;
		Network::CFDelta = MeanSquaredDelta;
	}
}

//copy constructor
Network::Network(const Network &obj) {
	printf("calling copy constructor \n");
}

//destructor
Network::~Network() {
	delete[] s;
	delete[] Tdims;
	delete[] adims;
	delete[] zdims;
	delete[] ddims;
	free(Jt);
	free(Jcv);
	free(Acct);
	free(Acccv);
	delete Theta;
	delete dTheta;
	if (TData) {
		delete[] yt;
		delete Xt;
		delete at;
		delete zt;
		delete delta;
	}
	if (CVData) {
		delete[] ycv;
		delete Xcv;
		delete acv;
		delete zcv;
	}
}

void Network::_GetOneHotClassLabels(int m, int *y0, Matrix &y) {
	/*******************************************************************
	 * This will convert an integer array into one-hot class labels.
	 * 
	 * ****************************************************************/
	int i, ind;
	for (i=0;i<m;i++) {
		ind = max(0,min(m-1,y0[i]));
		y->data[i][ind] = 1;
	}
}
	
void Network::_CreatePropagationMatrices(int m, Matrix &X, MatrixArray &z, MatrixArray &a, MatrixArray &delta) {
	/*******************************************************************
	 * This function should initialize some arrays for the propagation 
	 * of data through the network.
	 * ****************************************************************/
	int dims[Network::L*2];
	int i;
	
	for (i=0;i<Network::L;i++) {
		dims[i*2] = m;
		dims[i*2+1] = Network::s[i];
	}
	
	a = new MatrixArray(Network::L,dims);
	z = new MatrixArray(Network::L-1,&dims[2]);
	delta = new MatrixArray(Network::L,dims);
	a->matrix[0]->FillMatrix(X->data);	
}

//Self explanatory - input training data to network
void Network::InputTrainingData(int *xshape, double **xin, int ylen, int *yin){
	int i, j;

	if (xshape[1] != s[0]) {
		printf("X needs to have the dimensions (m,s1), where m is the number of training samples and s1 is equal to the number of units in the input layer of the network\n");
		return;
	}
	if (ylen != xshape[0]) {
		printf("y must have the dimensions (m,), where m is the number of training samples, and the value stored in yin should represent the output unit index or (m,k) where k is the number of outputs\n");
		return;
	}	

	/*enter data into relevant variables*/
	Network::mt = ylen;
	Network::Xt = new Matrix(Xshape,xin);
	Network::yt0 = CreateArray(Network::yt0,Network::mt);
	Network::yt = new Matrix(Network::mt,Network::s[Network::L-1]);
	Network::_GetOneHotClassLabels(Network::mt,Network::yt0,Network::yt);
	for (i=0;i<Network::mt;i++) {
		Network::yt0[i] = yin[i];
	}
	Network::TData = true;

	/*populate propagation arrays*/
	Network::_CreatePropagationMatrices(Network::mt,Network::Xt,Network::zt,Network::at,Network::deltat);

	/*Create Delta Matrices*/
	Network::_InitDeltaMatrices();

}


void Network::InputCrossValidationData(int *xshape, float **xin, int ylen, int *yin) {
	int i, j;

	if (xshape[1] != s[0]) {
		printf("X needs to have the dimensions (m,s1), where m is the number of CV samples and s1 is equal to the number of units in the input layer of the network\n");
		return;
	}
	if (ylen != xshape[0]) {
		printf("y must have the dimensions (m,), where m is the number of CV samples, and the value stored in yin should represent the output unit index or (m,k) where k is the number of outputs\n");
		return;
	}	

	/*enter data into relevant variables*/
	Network::mc = ylen;
	Network::Xc = new Matrix(Xshape,xin);
	Network::yc0 = CreateArray(Network::yc0,Network::mc);
	Network::yc = new Matrix(Network::mc,Network::s[Network::L-1]);
	Network::_GetOneHotClassLabels(Network::mc,Network::yc0,Network::yc);
	for (i=0;i<Network::mc;i++) {
		Network::yc0[i] = yin[i];
	}
	Network::CData = true;

	/*populate propagation arrays*/
	Network::_CreatePropagationMatrices(Network::mc,Network::Xc,Network::zc,Network::ac,Network::deltac);
}

void Network::InputTestData(int *xshape, double **xin, int ylen, int *yin){
	int i, j;

	if (xshape[1] != s[0]) {
		printf("X needs to have the dimensions (m,s1), where m is the number of test samples and s1 is equal to the number of units in the input layer of the network\n");
		return;
	}
	if (ylen != xshape[0]) {
		printf("y must have the dimensions (m,), where m is the number of test samples, and the value stored in yin should represent the output unit index or (m,k) where k is the number of outputs\n");
		return;
	}	

	/*enter data into relevant variables*/
	Network::mtest = ylen;
	Network::Xtest = new Matrix(Xshape,xin);
	Network::ytest0 = CreateArray(Network::ytest0,Network::mtest);
	Network::ytest = new Matrix(Network::mtest,Network::s[Network::L-1]);
	Network::_GetOneHotClassLabels(Network::mtest,Network::ytest0,Network::ytest);
	for (i=0;i<Network::mtest;i++) {
		Network::ytest0[i] = yin[i];
	}
	Network::TestData = true;

	/*populate propagation arrays*/
	Network::_CreatePropagationMatrices(Network::mtest,Network::Xtest,Network::ztest,Network::atest,Network::deltatest);
}

//this will train the network using either gradient-descent or conjugate-gradient minimization
void Network::Train() {
	
}

//gradient-descent
void Network::TrainGradientDescent(int MaxIter, float Alpha) {
	int i;
	for (i=0;i<MaxIter-1;i++) {
		Jt[nSteps] = CostFunction(*Theta,*at,*zt,yt,L,s,lambda);
		Acct[nSteps] = GetTrainingAccuracy();
		if (CVData) {
			Jcv[nSteps] = CostFunction(*Theta,*acv,*zcv,ycv,L,s,lambda);
			Acccv[nSteps] = GetCrossValidationAccuracy();			
			printf("\rI: %8d - Cost: %7e - T Acc: %6.2f - CV Cost: %7e - CV Acc: %6.2f",nSteps+1,Jt[nSteps],Acct[nSteps],Jcv[nSteps],Acccv[nSteps]);
		} else {
			printf("\rI: %8d - Cost: %10e - T Acc: %6.2f",nSteps+1,Jt[nSteps],Acct[nSteps]);
		}

		ThetaGradient(*Theta,*at,*delta,yt,L,s,lambda,*dTheta);
		UpdateTheta(*Theta,*dTheta,Alpha);
		nSteps++;
		if (nSteps >= nJ) {
			ExtendArrays();
		}
		if (isnan(Jt[nSteps-1]) || isinf(Jt[nSteps-1])) {
			printf("Cost function is NaN\n");
			break;
		}
	}
	Jt[nSteps] = CostFunction(*Theta,*at,*zt,yt,L,s,lambda);
	Acct[nSteps] = GetTrainingAccuracy();
	if (CVData) {
		Jcv[nSteps] = CostFunction(*Theta,*acv,*zcv,ycv,L,s,lambda);
		Acccv[nSteps] = GetCrossValidationAccuracy();			
		printf("\rI: %8d - Cost: %7e - T Acc: %6.2f - CV Cost: %10e - CV Acc: %6.2f\n",nSteps+1,Jt[nSteps],Acct[nSteps],Jcv[nSteps],Acccv[nSteps]);
	} else {
		printf("\rI: %8d - Cost: %7e - T Acc: %6.2f\n",nSteps+1,Jt[nSteps],Acct[nSteps]);
	}	
	nSteps++;
	Trained = true;
}

void Network::TrainGradientDescentQuiet(int MaxIter, float Alpha) {
	int i;
	for (i=0;i<MaxIter-1;i++) {
		Jt[nSteps] = CostFunction(*Theta,*at,*zt,yt,L,s,lambda);
		Acct[nSteps] = GetTrainingAccuracy();
		if (CVData) {
			Jcv[nSteps] = CostFunction(*Theta,*acv,*zcv,ycv,L,s,lambda);
			Acccv[nSteps] = GetCrossValidationAccuracy();			
		}

		ThetaGradient(*Theta,*at,*delta,yt,L,s,lambda,*dTheta);
		UpdateTheta(*Theta,*dTheta,Alpha);
		nSteps++;
		if (nSteps >= nJ) {
			ExtendArrays();
		}
		if (isnan(Jt[nSteps-1]) || isinf(Jt[nSteps-1])) {
			printf("\nCost function is NaN\n");
			break;
		}
	}
	Jt[nSteps] = CostFunction(*Theta,*at,*zt,yt,L,s,lambda);
	Acct[nSteps] = GetTrainingAccuracy();
	if (CVData) {
		Jcv[nSteps] = CostFunction(*Theta,*acv,*zcv,ycv,L,s,lambda);
		Acccv[nSteps] = GetCrossValidationAccuracy();			
	}
	nSteps++;
	Trained = true;
}



//conjugate-gradient
void Network::TrainConjugateGradient() {
	
}

//this will calculate how accurately the network classifies the training
//set, where variable at is always updated after being passed to CostFunction
float Network::GetTrainingAccuracy() {
	int yp[mt];
	int i, good = 0;
	Predict(*at->matrix[L-1],yp);
	for (i=0;i<mt;i++) {
		good += (int) (yp[i] == yt[i]);
	}
	return ((float) good)/((float) mt)*100.0;
}

//as above, but for the CV set
float Network::GetCrossValidationAccuracy() {
	int yp[mcv];
	int i, good = 0;
	Predict(*acv->matrix[L-1],yp);
	for (i=0;i<mcv;i++) {
		good += (int) (yp[i] == ycv[i]);
	}
	return ((float) good)/((float) mcv)*100.0;	
}

//this will forward propagate input data through the network and either 
//classifiy it definitively, or provide probabilities using the softmax function
void Network::ClassifyData(int *xshape, float *xin, int m, int *yout) {
	Matrix *Xtest;
	int i, Xshape[] = {m,s[0]+1}, zdimstest[(L-1)*2], adimstest[L*2];
	Xtest = new Matrix(Xshape);
	Xtest->FillWithBias(xin);
	for (i=0;i<L;i++) {
		if (i > 0) { 
			zdimstest[i*2 - 2] = m;
			zdimstest[i*2 - 1] = s[i];	
		}
		if (i== L-1) {
			adimstest[i*2] = m;
			adimstest[i*2 + 1] = s[i];

		} else {
			adimstest[i*2] = m;
			adimstest[i*2 + 1] = s[i] + 1;
		}
	}
	
	atest = new MatrixArray(L,adimstest);
	ztest = new MatrixArray(L-1,zdimstest);
	
	atest->matrix[0]->FillMatrix(Xtest->data);	
	Propagate(*atest,*ztest,*Theta,L);
	Predict(*atest->matrix[L-1],yout);
	
	delete atest;
	delete ztest;
	delete Xtest;
}



void Network::ClassifyData(int *xshape, float *xin, int m, int *yout, float *SMout) {
	Matrix *Xtest;
	int i, Xshape[] = {m,s[0]+1}, zdimstest[(L-1)*2], adimstest[L*2];
	Xtest = new Matrix(Xshape);
	Xtest->FillWithBias(xin);
	for (i=0;i<L;i++) {
		if (i > 0) { 
			zdimstest[i*2 - 2] = m;
			zdimstest[i*2 - 1] = s[i];	
		}
		if (i== L-1) {
			adimstest[i*2] = m;
			adimstest[i*2 + 1] = s[i];

		} else {
			adimstest[i*2] = m;
			adimstest[i*2 + 1] = s[i] + 1;
		}
	}
	
	atest = new MatrixArray(L,adimstest);
	ztest = new MatrixArray(L-1,zdimstest);
	
	atest->matrix[0]->FillMatrix(Xtest->data);	
	Propagate(*atest,*ztest,*Theta,L);
	Predict(*atest->matrix[L-1], yout);
	
	int K = s[L-1];
	int smshape[] = {m,K};
	Matrix SM(smshape);
	
	PredictProbs(*ztest->matrix[L-2],SM);
	
	for (i=0;i<SM.len;i++) {
		SMout[i] = SM.data[i];
	}
	
	delete atest;
	delete ztest;
	delete Xtest;
}


void Network::Save(const char *fname) {
	int i;
	FILE *f;
	f = fopen(fname,"wb");
	fwrite(&Trained,sizeof(bool),1,f);
	fwrite(&L,sizeof(int),1,f);
	fwrite(s,sizeof(int),L,f);
	fwrite(&lambda,sizeof(float),1,f);
	fwrite(&range,sizeof(float),1,f);
	fwrite(&mt,sizeof(int),1,f);
	fwrite(&mcv,sizeof(int),1,f);	
	
	if (TData) {
		fwrite(Xt->data,sizeof(float),Xt->len,f);
		fwrite(yt,sizeof(int),mt,f);
	}
	if (CVData) {
		fwrite(Xcv->data,sizeof(float),Xcv->len,f);
		fwrite(ycv,sizeof(int),mcv,f);
	}
	for (i=0;i<L-1;i++) {
		fwrite(Theta->matrix[i]->data,sizeof(float),Theta->matrix[i]->len,f);
	}
	fwrite(&nSteps,sizeof(int),1,f);
	fwrite(&nJ,sizeof(int),1,f);	
	fwrite(Jt,sizeof(float),nJ,f);
	fwrite(Jcv,sizeof(float),nJ,f);
	fwrite(Acct,sizeof(float),nJ,f);
	fwrite(Acccv,sizeof(float),nJ,f);
	fclose(f);
}

int Network::GetnSteps() {
	return nSteps;
}

void Network::GetTrainingAccuracy(float *Jtout, float *Actout) {
	int i;
	for (i=0;i<nSteps;i++) {
		Jtout[i] = Jt[i];
		Actout[i] = Acct[i];
	}
}

void Network::GetCrossValidationAccuracy(float *Jcvout, float *Accvout) {
	int i;
	for (i=0;i<nSteps;i++) {
		Jcvout[i] = Jcv[i];
		Accvout[i] = Acccv[i];
	}
}


void Network::GetLastCrossValidationAccuracy(float *Jcvout, float *Accvout) {
	int i;
	Jcvout[0] = Jcv[nSteps-1];
	Accvout[0] = Acccv[nSteps-1];

}

int Network::GetL() {
	return L;
}

void Network::Gets(int *sout) {
	int i;
	for (i=0;i<L;i++) {
		sout[i] = s[i];
	}
}

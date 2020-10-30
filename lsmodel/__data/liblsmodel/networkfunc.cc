#include "networkfunc.h"

NetworkFunc::NetworkFunc(int L, int *s, const char * sHiddenFunc,
						const char *sOutFunc, const char *sCostFunc) {
	
	/* copy the network architecture */
	L_ = L;
	int i;
	s_ = new int[L_];
	for (i=0;i<L_;i++) {
		s_[i] = s[i];
	}
	
	/* define the shapes of the matrices */
	int nm = L_ - 1;
	int ws[nm*2];
	int bs[nm*2];
	
	for (i=0;i<nm;i++) {
		ws[i*2] = s_[i];
		ws[i*2+1] = s_[i+1];
		bs[i*2] = 1;
		bs[i*2 + 1] = s_[i+1];
	}
	
	/* create some empty matrices */
	W_ = new MatrixArray(nm,ws);
	B_ = new MatrixArray(nm,bs);
	
	/* empty scaling factors */
	scale0_ = new float[s_[L_-1]];
	scale1_ = new float[s_[L_-1]];
	for (i=0;i<s_[L_-1];i++) {
		scale0_[i] = 1.0;
		scale1_[i] = 0.0;
	}
	
	/* get the cost function */
	_SetCostFunction(sCostFunc);
	
	/* get the activation functions */
	_PopulateActivationFunctions(sHiddenFunc,sOutFunc);	
	
	/* dummy cost function arrays */
	nEpoch_ = 1;
	Jt_ = new float[nEpoch_];
	Jc_ = new float[nEpoch_];
							
}

NetworkFunc::NetworkFunc(unsigned char *ptr, const char * sHiddenFunc,
						const char *sOutFunc, const char *sCostFunc) {
							
	
	/* create a local copy of the pointer */
	unsigned char *p = ptr;
	
	
	/* Read in s first (also L) */
	p = readArray(p,&s_,&L_);
	
	/* read in the rescaling parameters */
	int itmp;
	p = readArray(p,&scale0_,&itmp);
	p = readArray(p,&scale1_,&itmp);

	/* now read in the matrices */
	W_ = new MatrixArray(&p);
	B_ = new MatrixArray(&p);

	/* now read the cost functions */
	p = readArray(p,&Jt_,&nEpoch_);
	p = readArray(p,&Jc_,&nEpoch_);
	
	/* get the cost function */
	_SetCostFunction(sCostFunc);
	
	/* get the activation functions */
	_PopulateActivationFunctions(sHiddenFunc,sOutFunc);
	
}


NetworkFunc::NetworkFunc(const NetworkFunc &obj) {
	
	
}

NetworkFunc::~NetworkFunc() {
	
	/* delete everything created in the constructor */
	delete s_;
	delete scale0_;
	delete scale1_;
	delete W_;
	delete B_;
	delete Jt_;
	delete Jc_;
	delete AF_;
	
}


void NetworkFunc::_SetCostFunction(const char *sCostFunc) {
	
	if (strcmp(sCostFunc,"mean_squared") == 0) {
		/* set to the mean squared function */
		CF_ = &meanSquaredCost;
	} else if (strcmp(sCostFunc,"cross_entropy") == 0) {
		/* set to the cross entropy function */
		CF_ = &crossEntropyCost;
	} else {
		/*if all else fails - set it to the mean squared function */
		CF_ = &meanSquaredCost;
	}
	
}

void NetworkFunc::_PopulateActivationFunctions(const char *sHiddenFunc, const char *sOutFunc) {
	
	/* if we have L layers, we need L-1 AFs, where AF[0] - AF[L-3] will
	 * be the sHiddenFunc and AF[L-2] will be sOutFunc */
	int i;
	ActFunc HF = AFFromString(sHiddenFunc);
	ActFunc OF = AFFromString(sOutFunc);
	
	/* allocate the pointer array */
	AF_ = new ActFunc[L_-1];
	
	/* set the hidden ones */
	for (i=0;i<L_-2;i++) {
		AF_[i] = HF;
	}
	
	/* and the output one */
	AF_[L_-2] = OF;
	
}
	 
MatrixArray* NetworkFunc::_CreatePropagationMatrices(int n) {
	
	/* get the matrix shapes first */
	int i;
	int nMat = L_;
	int mShapes[nMat*2];
	for (i=0;i<L_;i++) {
		mShapes[i*2 + 1] = s_[i];
		mShapes[i*2] = n;
	}
	
	/* create the array */
	MatrixArray *out = new MatrixArray(nMat,mShapes);

	return out;
	
}

void NetworkFunc::Predict(int n, float **in, float **out) {
	/* input shape should be (n,m) where n is the number of samples,
	 * m is the number of features.
	 * Output shape should be (n,k) where k is the number of output 
	 * nodes */
	
	char str[10];
	/* create propagation matrices */
	MatrixArray *pmat = _CreatePropagationMatrices(n);
	
	/* enter the initial data */
	pmat->matrix[0]->FillMatrix(in);

	/* propagate through the matrices */
	int i;
	for (i=0;i<L_-1;i++) {
		/* multiply w*x */
		MatrixDot(*pmat->matrix[i],*W_->matrix[i],false,false,*pmat->matrix[i+1]);
		
		/* add the bias */
		AddBiasVectorToMatrix(*pmat->matrix[i+1],*B_->matrix[i]);


		/* apply the activation function */
		ApplyFunctionToMatrix(*pmat->matrix[i+1],AF_[i],*pmat->matrix[i+1]);

	}

	/* rescale data */
	_RescaleOut(*pmat->matrix[L_-1]);

	/* fill the output array */
	pmat->matrix[L_-1]->ReturnMatrix(out);
	
	/* delete the propagation matrix again */
	delete pmat;
}

void NetworkFunc::_RescaleOut(Matrix &m) {
	
	int i, j;
	
	for (i=0;i<m.shape[0];i++) {
		for (j=0;j<m.shape[1];j++) {
			m.data[i][j] = m.data[i][j]/scale0_[j] + scale1_[j];
		}
	}
}

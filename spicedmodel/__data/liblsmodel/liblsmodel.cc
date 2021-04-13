#include "liblsmodel.h"

/***********************************************************************
 * NAME : 	void initModels()
 * 
 * DESCRIPTION : 
 * 		Initializes the model objects.
 * 
 * ********************************************************************/
void initModels() {
	/* check if the average models are loaded */
	if (gAvMavH == NULL) {
		gAvMavH = new AvMavHModel(&_binary_mavh_bin_start);
	}
	if (gAvMavPS == NULL) {
		gAvMavPS = new AvMavPSModel(&_binary_mavcps_bin_start);
	}
	if (gAvMavPT == NULL) {
		gAvMavPT = new AvMavPTModel(&_binary_mavcpt_bin_start);
	}
	if (gAvProb == NULL) {
		gAvProb = new AvProbModel(&_binary_prob_bin_start);
	}
	if (gAvPS == NULL) {
		gAvPS = new AvPSModel(&_binary_ps_bin_start);
	}
	if (gAvPT == NULL) {
		gAvPT = new AvPTModel(&_binary_pt_bin_start);
	}
	
	/* check if the ANN models are loaded */
	if (gAnnMavH == NULL) {
		gAnnMavH = new ANNMavHModel(&_binary_mavhann_bin_start);
	}
	if (gAnnMavPS == NULL) {
		gAnnMavPS = new ANNMavPSModel(&_binary_mavcpsann_bin_start);
	}
	if (gAnnMavPT == NULL) {
		gAnnMavPT = new ANNMavPTModel(&_binary_mavcptann_bin_start);
	}
	if (gAnnProb == NULL) {
		gAnnProb = new ANNProbModel(&_binary_probann_bin_start);
	}
	if (gAnnPS == NULL) {
		gAnnPS = new ANNPSModel(&_binary_psann_bin_start);
	}
	if (gAnnPT == NULL) {
		gAnnPT = new ANNPTModel(&_binary_ptann_bin_start);
	}
	
}

/***********************************************************************
 * NAME : 	void getAvMavH(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavH(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavH->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMavHCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavHCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavH->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledMavH(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*f107		Array of F10.7 indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavH(int n, float *mlt, float *R, float *f107, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavH->Model(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledMavHCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*f107		Array of F10.7 indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavHCart(int n, float *x, float *y, float *f107, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavH->ModelCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMavPT(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavPT(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMavPTCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavPTCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledMavPT(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavPT(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledMavPTCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavPTCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getAvMavPS(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavPS(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMavPSCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavPSCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvMavPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledMav(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavPS(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledMavPSCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavPSCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMavPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getAvProb(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvProb(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvProb->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getAvProbCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvProbCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledProb(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledProb(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledProbCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledProbCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnProb->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}

/***********************************************************************
 * NAME : 	void getAvPS(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	If true, reverses transformed densities to 
 * 							real units.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPS(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvPSCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPSCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledPS(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPS(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledPSCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPSCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvPT(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasma trough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	If true, reverses transformed densities to 
 * 							real units.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPT(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvPTCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPTCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledPT(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPT(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledPTCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPTCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMav(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough average ion 
 * 		mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMav(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *mavps = new float[n];
	float *mavpt = new float[n];
	
	/* run the models */
	gAvProb->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvMavPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAvMavPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = mavps[i];
		} else { 
			out[i] = mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete mavps;
	delete mavpt;
	
}

/***********************************************************************
 * NAME : 	void getAvMavCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough average ion 
 * 		mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *mavps = new float[n];
	float *mavpt = new float[n];
	
	/* run the models */
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvMavPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAvMavPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = mavps[i];
		} else { 
			out[i] = mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete mavps;
	delete mavpt;
	
}

/***********************************************************************
 * NAME : 	void getScaledMav(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough average ion mass
 * 		model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMav(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *mavps = new float[n];
	float *mavpt = new float[n];
	
	/* run the models */
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnMavPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAnnMavPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = mavps[i];
		} else { 
			out[i] = mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete mavps;
	delete mavpt;
	
}

/***********************************************************************
 * NAME : 	void getScaledMavCart(n,x,y,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough average ion mass
 * 		model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *mavps = new float[n];
	float *mavpt = new float[n];
	
	/* run the models */
	gAnnProb->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnMavPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAnnMavPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = mavps[i];
		} else { 
			out[i] = mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete mavps;
	delete mavpt;
	
}

/***********************************************************************
 * NAME : 	void getAvDen(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvDen(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvProb->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i];
		} else { 
			out[i] = pt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getAvDenCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvDenCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i];
		} else { 
			out[i] = pt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getScaledDen(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledDen(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i];
		} else { 
			out[i] = pt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getScaledDenCart(n,x,y,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledDenCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnProb->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i];
		} else { 
			out[i] = pt[i];
		}
	}
	
	/* delete temporary arrays */
	delete prob;
	delete ps;
	delete pt;
	
}


/***********************************************************************
 * NAME : 	void getAvPMD(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough plasma mass
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPMD(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mavps = new float[n];
	float *mavpt = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvMavPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAvMavPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	gAvProb->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mavps[i];
		} else { 
			out[i] = pt[i]*mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete mavps;
	delete mavpt;
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getAvPMDCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough plasma mass
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvPMDCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mavps = new float[n];
	float *mavpt = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvMavPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAvMavPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,pt);

	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mavps[i];
		} else { 
			out[i] = pt[i]*mavpt[i];
		}
	}

	/* delete temporary arrays */
	delete mavps;
	delete mavpt;
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getScaledPMD(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPMD(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mavps = new float[n];
	float *mavpt = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnMavPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAnnMavPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mavps[i];
		} else { 
			out[i] = pt[i]*mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete mavps;
	delete mavpt;
	delete prob;
	delete ps;
	delete pt;
	
}

/***********************************************************************
 * NAME : 	void getScaledPMDCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledPMDCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mavps = new float[n];
	float *mavpt = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnMavPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavps);
	gAnnMavPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,mavpt);
	gAnnProb->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mavps[i];
		} else { 
			out[i] = pt[i]*mavpt[i];
		}
	}
	
	/* delete temporary arrays */
	delete mavps;
	delete mavpt;
	delete prob;
	delete ps;
	delete pt;
	
}

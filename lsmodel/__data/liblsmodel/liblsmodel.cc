#include "liblsmodel.h"


void initModels() {
	/* check if the average models are loaded */
	if (gAvMav == NULL) {
		gAvMav = new AvMavModel(&_binary_mav_bin_start);
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
	if (gAnnMav == NULL) {
		gAnnMav = new ANNMavModel(&_binary_mavann_bin_start);
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
 * NAME : 	void getAvMav(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the average ion mass model.
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
	
	/* run the model */
	gAvMav->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getAvMavCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E)
 * 		float 	*y			Array of y-position (SM coords, in R_E)
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
	
	/* run the model */
	gAvMav->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}

/***********************************************************************
 * NAME : 	void getScaledMav(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled average ion mass model.
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
void getScaledMav(int n, float *mlt, float *R, float *f107, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMav->Model(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


/***********************************************************************
 * NAME : 	void getScaledMavCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E)
 * 		float 	*y			Array of y-position (SM coords, in R_E)
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
void getScaledMavCart(int n, float *x, float *y, float *f107, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnMav->ModelCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out);
	
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



void getAvProbCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}


void getScaledProb(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out);
	
}



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



void getAvPSCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


void getScaledPS(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}



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



void getAvPTCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAvPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


void getScaledPT(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}



void getScaledPTCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* run the model */
	gAnnPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
	
}


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



void getAvPMD(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mav = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvMav->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,mav);
	gAvProb->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mav[i];
		} else { 
			out[i] = pt[i]*mav[i];
		}
	}
	
	/* delete temporary arrays */
	delete mav;
	delete prob;
	delete ps;
	delete pt;
	
}

void getAvPMDCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mav = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAvMav->Model(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,mav);
	gAvProb->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAvPS->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAvPT->ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mav[i];
		} else { 
			out[i] = pt[i]*mav[i];
		}
	}
	
	/* delete temporary arrays */
	delete mav;
	delete prob;
	delete ps;
	delete pt;
	
}


void getScaledPMD(int n, float *mlt, float *R, float *f107, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mav = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnMav->Model(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,mav);
	gAnnProb->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mav[i];
		} else { 
			out[i] = pt[i]*mav[i];
		}
	}
	
	/* delete temporary arrays */
	delete mav;
	delete prob;
	delete ps;
	delete pt;
	
}

void getScaledPMDCart(int n, float *x, float *y, float *f107, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out) {
	
	/* check that the models have been loaded first */
	initModels();
	
	/* create some temporary arrays */
	float *mav = new float[n];
	float *prob = new float[n];
	float *ps = new float[n];
	float *pt = new float[n];
	
	/* run the models */
	gAnnMav->Model(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,mav);
	gAnnProb->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,prob);
	gAnnPS->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,ps);
	gAnnPT->ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,true,pt);
	
	/* select the appropriate densities base upon prob */
	int i;
	for (i=0;i<n;i++) {
		if (prob[i] >= 0.5) {
			out[i] = ps[i]*mav[i];
		} else { 
			out[i] = pt[i]*mav[i];
		}
	}
	
	/* delete temporary arrays */
	delete mav;
	delete prob;
	delete ps;
	delete pt;
	
}

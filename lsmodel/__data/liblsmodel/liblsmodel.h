#ifndef __LIBLSMODEL_H__
#define __LIBLSMODEL_H__
#include <stdio.h>
#include <stdlib.h>

#include "avmavhmodel.h"
#include "avmavpsmodel.h"
#include "avmavptmodel.h"
#include "annmavhmodel.h"
#include "annmavpsmodel.h"
#include "annmavptmodel.h"
#include "avprobmodel.h"
#include "annprobmodel.h"
#include "avpsmodel.h"
#include "annpsmodel.h"
#include "avptmodel.h"
#include "annptmodel.h"
#endif
using namespace std;

/* these are the memory addresses for the average model parameters */
extern unsigned char _binary_mavh_bin_start;
extern unsigned char _binary_mavcps_bin_start;
extern unsigned char _binary_mavcpt_bin_start;
extern unsigned char _binary_prob_bin_start;
extern unsigned char _binary_ps_bin_start;
extern unsigned char _binary_pt_bin_start;

/* these are the memory addresses for the ANN model parameters */
extern unsigned char _binary_mavhann_bin_start;
extern unsigned char _binary_mavcpsann_bin_start;
extern unsigned char _binary_mavcptann_bin_start;
extern unsigned char _binary_probann_bin_start;
extern unsigned char _binary_psann_bin_start;
extern unsigned char _binary_ptann_bin_start;

/* this is where the models will be stored during runtime */
AvMavHModel *gAvMavH = NULL;
AvMavPSModel *gAvMavPS = NULL;
AvMavPTModel *gAvMavPT = NULL;
AvProbModel *gAvProb = NULL;
AvPSModel *gAvPS = NULL;
AvPTModel *gAvPT = NULL;

ANNMavHModel *gAnnMavH = NULL;
ANNMavPSModel *gAnnMavPS = NULL;
ANNMavPTModel *gAnnMavPT = NULL;
ANNProbModel *gAnnProb = NULL;
ANNPSModel *gAnnPS = NULL;
ANNPTModel *gAnnPT = NULL;


/***********************************************************************
 * NAME : 	void initModels()
 * 
 * DESCRIPTION : 
 * 		Initializes the model objects.
 * 
 * ********************************************************************/
void initModels();


extern "C" {
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
				bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, float *out);
				
				
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
				bool OnlyDC, bool Validate, int m0, int m1, float *out);


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
				bool OnlyDC,bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);


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
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);


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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);


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
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);


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
				bool Validate, int m0, int m1, float *out);


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
				bool Validate, int m0, int m1, float *out);
				
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
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

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
				bool OnlyDC,bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool Validate, int m0, int m1, bool RevTrans, float *out);
				
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
				bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);

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
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);


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
				bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

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
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, float *out);

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
				bool Validate, int m0, int m1, float *out) ;

/***********************************************************************
 * NAME : 	void getScaledPMD(n,mlt,R,f107,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*f107		Array of F10.7 indices.
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
	void getScaledPMD(int n, float *mlt, float *R, float *f107, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledPMDCart(n,x,y,f107,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*f107		Array of F10.7 indices.
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
	void getScaledPMDCart(int n, float *x, float *y, float *f107, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);
}

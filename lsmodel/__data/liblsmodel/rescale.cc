#include "rescale.h"

/* some scaling factors for SMR */
const double gSMRshift = 249.0968475341796875;
const double gSMRlambda = 2.666015625;
const double gSMRmu = 882455.6875;
const double gSMRsigma = 128960.2265625;

/* scaling factors for the f10.7 index */
const double gF107shift = 0.0;
const double gF107lambda = -0.146484375;
const double gF107mu = 3.36984705924987792969;
const double gF107sigma = 0.13723261654376983643;

/* scaling factors for the density */
const double gDenshift = 0.0;
const double gDenlambda = 0.0654296875;
const double gDenmu = 5.30398035049438476562;
const double gDensigma = 2.49992799758911132812;

/***********************************************************************
 * NAME : float rescaleSMR(smr)
 * 
 * DESCRIPTION : Rescales the SMR index so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	smr		The SMR index.
 * 
 * RETURNS : 
 * 		float	smrt 	The rescaled SMR index.
 * 
 * ********************************************************************/
float rescaleSMR(float smr) {
	return BoxCox(smr,gSMRlambda,gSMRshift,gSMRmu,gSMRsigma);
}

/***********************************************************************
 * NAME : float rescaleF107(f107)
 * 
 * DESCRIPTION : Rescales the F10.7 index so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	f107	The F10.7 index.
 * 
 * RETURNS : 
 * 		float	f107t 	The rescaled F10.7 index.
 * 
 * ********************************************************************/
float rescaleF107(float f107) {
	return BoxCox(f107,gF107lambda,gF107shift,gF107mu,gF107sigma);
}

/***********************************************************************
 * NAME : float rescaleR(R)
 * 
 * DESCRIPTION : Rescales the L-shell so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	R		The L-shell.
 * 
 * RETURNS : 
 * 		float	Rt 		The rescaled L-shell.
 * 
 * ********************************************************************/
float rescaleR(float R) {
	return (R - 4.0)/2.0;
}

/***********************************************************************
 * NAME : float unscaleDensity(dt)
 * 
 * DESCRIPTION : Reverses the Box-Cox transform of the density output
 * 				from the ANN.
 * 
 * INPUTS : 
 * 		float	dt		The transformed density output from the ANN.
 * 
 * RETURNS : 
 * 		float	d		Density in real units.
 * 
 * ********************************************************************/
float unscaleDensity(float dt) {
	return ReverseBoxCox(dt,gDenlambda,gDenshift,gDenmu,gDensigma);	
}

#ifndef __RESCALE_H__
#define __RESCALE_H__
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "boxcox.h"
#endif
using namespace std;

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
float rescaleSMR(float smr);

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
float rescaleF107(float f107);

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
float rescaleR(float R);

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
float unscaleDensity(float dt);

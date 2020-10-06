#ifndef __AVMODEL_H__
#define __AVMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "readarray.h"
#include <algorithm>
#include "polynomial.h"
#include <math.h>
#include "reversearray.h"

using namespace std;

/***********************************************************************
 * NAME : 	class AvModel
 * 
 * DESCRIPTION : This is hte basic model class object for storing the
 * 				average model parameters. This class should not be used
 * 				directly, it should be inherited by one of the other 
 * 				model classes.
 * 
 * 
 * ********************************************************************/
class AvModel {
	public:
		/* these pointers will be used to store the model variables */
		int ndc_, Rshape_[2], Ishape_[2];
		float *dc_, **R_, **I_;
		
		/* this is for storing the number of m-numbers */
		int nm_;
		int *m_;
		float *wl_;
		
		/* read in the model variables */
		void ReadModelParams(unsigned char *);
		
		/* calculate the model components */
		void PeriodicComponents(int,float*,float*,float**);
		
		/* Cartesian to MLT and R */
		void CartMLTR(int,float*,float*,float*,float*);
};
#endif

#ifndef __ANNMODEL_H__
#define __ANNMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "networkfunc.h"
#include "rescale.h"
using namespace std;

/***********************************************************************
 * NAME : 	class ANNModel
 * 
 * DESCRIPTION : This is the basic model class object for storing the 
 * 				ANN object and obtaining the model parameters. This 
 * 				class should not be used directly, it should be 
 * 				inherited by one of the other model classes.
 * 
 * 
 * ********************************************************************/
class ANNModel {
	public:
		/* This ann will provide the components of the model */
		NetworkFunc *ann_;
		
		/* Load the neural network */
		void LoadANN(unsigned char *);
		
		/* calculate the model components */
		/* Calculate the model components */
		void ModelComponents(int,float*,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float*,float**);

		/* Cartesian to MLT and R */
		void CartMLTR(int,float*,float*,float*,float*);
		
		/* we need to know the number of m-numbers */
		int nm_, *m_;
		
		/* frequencies */
		float *wl_;
};
#endif

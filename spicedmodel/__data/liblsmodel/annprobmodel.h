#ifndef __ANNPROBMODEL_H__
#define __ANNPROBMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;

/***********************************************************************
 * NAME : 	class ANNProbModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the probability model neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class ANNProbModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNProbModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNProbModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,float*);	
};
#endif



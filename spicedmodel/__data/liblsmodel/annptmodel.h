#ifndef __ANNPTMODEL_H__
#define __ANNPTMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;


/***********************************************************************
 * NAME : 	class ANNPTModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the plasma trough model neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class ANNPTModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNPTModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNPTModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	
};
#endif


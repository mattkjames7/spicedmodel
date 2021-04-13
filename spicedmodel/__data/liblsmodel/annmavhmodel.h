#ifndef __ANNMAVHMODEL_H__
#define __ANNMAVHMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;

/***********************************************************************
 * NAME : 	class ANNMavHModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the average ion mass neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is for hot ions!!!
 * 
 * ********************************************************************/
class ANNMavHModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavHModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavHModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,float*);	
};

#endif


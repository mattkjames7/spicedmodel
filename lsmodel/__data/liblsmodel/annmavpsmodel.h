#ifndef __ANNMAVPSMODEL_H__
#define __ANNMAVPSMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;

/***********************************************************************
 * NAME : 	class ANNMavPSModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the average ion mass neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * 				This is the cold ion plasmsphere model!
 * 
 * ********************************************************************/
class ANNMavPSModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavPSModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavPSModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	

	private:
		MavTrans *MT_;
};

#endif


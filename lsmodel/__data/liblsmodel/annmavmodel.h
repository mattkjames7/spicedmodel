#ifndef __ANNMAVMODEL_H__
#define __ANNMAVMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;


#endif
class ANNMavModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavModel();
		

		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,float*);	
};


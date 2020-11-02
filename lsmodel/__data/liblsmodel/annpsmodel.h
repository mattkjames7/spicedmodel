#ifndef __ANNPSMODEL_H__
#define __ANNPSMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "annmodel.h"
using namespace std;


class ANNPSModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNPSModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNPSModel();
		

		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	
};
#endif


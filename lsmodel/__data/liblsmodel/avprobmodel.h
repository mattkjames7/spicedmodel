#ifndef __AVPROBMODEL_H__
#define __AVPROBMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "avmodel.h"
#include <algorithm>

/***********************************************************************
 * NAME : 	class AvProbModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average probability model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class AvProbModel: public AvModel {
	public:
		/* model constructor */
		AvProbModel(unsigned char *);
		
		/* model destructor */
		~AvProbModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,float*);
};

#endif


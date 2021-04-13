#ifndef __AVMAVHMODEL_H__
#define __AVMAVHMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "avmodel.h"
#include <algorithm>

/***********************************************************************
 * NAME : 	class AvMavHModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average ion mass model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is the hot average ion mass model - it bares
 * 				little resemblance to the cold composition.
 * 
 * ********************************************************************/
class AvMavHModel: public AvModel {
	public:
		/* model constructor */
		AvMavHModel(unsigned char *);
		
		/* model destructor */
		~AvMavHModel();
		
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

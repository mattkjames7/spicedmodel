#ifndef __AVMAVPSMODEL_H__
#define __AVMAVPSMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "avmodel.h"
#include <algorithm>
#include "mavtrans.h"

/***********************************************************************
 * NAME : 	class AvMavPSModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average ion mass model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is the cold ion model.
 * 
 * ********************************************************************/
class AvMavPSModel: public AvModel {
	public:
		/* model constructor */
		AvMavPSModel(unsigned char *);
		
		/* model destructor */
		~AvMavPSModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
	private:
		MavTrans *MT_;
};


#endif

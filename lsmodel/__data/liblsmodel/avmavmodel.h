#ifndef __AVMAVMODEL_H__
#define __AVMAVMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "avmodel.h"
#include <algorithm>

class AvMavModel: public AvModel {
	public:
		/* model constructor */
		AvMavModel(unsigned char *);
		
		/* model destructor */
		~AvMavModel();
		
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

#ifndef __AVPTMODEL_H__
#define __AVPTMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "avmodel.h"
#include <algorithm>
#include "boxcox.h"
#include "polynomial.h"
#include "reversearray.h"
#endif
class AvPTModel: public AvModel {
	public:
		/* model constructor */
		AvPTModel(unsigned char *);
		
		/* model destructor */
		~AvPTModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
};



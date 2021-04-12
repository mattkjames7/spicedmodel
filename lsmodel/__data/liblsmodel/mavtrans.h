#ifndef __MAVTRANS_H__
#define __MAVTRANS_H__
#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"
#include "reversearray.h"
#include "readarray.h"
using namespace std;
extern unsigned char _binary_mavlambda_bin_start;

/***********************************************************************
 * NAME : 	class MavTrans
 * 
 * DESCRIPTION : This object will handle the transformation of average
 * 			ion masses. We use a Box-Cox transform where lambda is a 
 * 			non-linear function of R.
 * 
 * 
 * ********************************************************************/

class MavTrans {
	public:
		MavTrans();
		~MavTrans();
		void PSTransform(int,float*,float*,float*);
		void PTTransform(int,float*,float*,float*);
		void PSRevTransform(int,float*,float*,float*);
		void PTRevTransform(int,float*,float*,float*);
	private:
		void ReadCoefficients();
	
		/*These are the number of degrees in the polynomials*/
		int nps_,npt_;
		
		/* polynomial coefficients */
		float *ps_, *pt_;
};

#endif



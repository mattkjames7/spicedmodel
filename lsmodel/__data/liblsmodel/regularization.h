#ifndef __REGULARIZATION_H__
#define __REGULARIZATION_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixarray.h"
#include <omp.h>
using namespace std;

/***********************************************************************
 * NAME : 	float L1Regularization(w,L1,m)
 * 
 * DESCRIPTION : Calculates the L1 regularization.
 * 
 * INPUTS : 
 * 		MatrixArray	&w	Network weight matrices
 * 		float		L1	L1 regularization parameter
 * 		int			m	Number of samples.
 * 
 * RETURNS : 
 * 		float 	The additional cost due to regularization.
 * 
 * ********************************************************************/
float L1Regularization(MatrixArray &w, float L1, int m);

/***********************************************************************
 * NAME : 	float L2Regularization(w,L1,m)
 * 
 * DESCRIPTION : Calculates the L2 regularization.
 * 
 * INPUTS : 
 * 		MatrixArray	&w	Network weight matrices
 * 		float		L2	L2 regularization parameter
 * 		int			m	Number of samples.
 * 
 * RETURNS : 
 * 		float 	The additional cost due to regularization.
 * 
 * ********************************************************************/
float L2Regularization(MatrixArray &w, float L2, int m);
#endif

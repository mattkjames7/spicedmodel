#ifndef __CLIPLOG_H__
#define __CLIPLOG_H__
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;


/***********************************************************************
 * NAME : 	float cliplog(x,min)
 * 
 * DESCRIPTION : This function will clip values of x before passing to 
 * 					the log function so that there are not -inf's, a 
 * 					good value for min is 1e-40
 * 
 * INPUTS :
 * 		float	x	The value to be loged
 * 		float 	mn	Minimum value
 * 
 * RETURNS :
 * 		float	log(x)	Log of x
 * 	
 * ********************************************************************/
float cliplog(float x, float mn);
#endif

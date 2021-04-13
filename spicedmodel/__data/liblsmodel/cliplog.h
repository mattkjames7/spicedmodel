#ifndef __CLIPLOG_H__
#define __CLIPLOG_H__
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;


/***********************************************************************
 * NAME : 	double cliplog(x,min)
 * 
 * DESCRIPTION : This function will clip values of x before passing to 
 * 					the log function so that there are not -inf's, a 
 * 					good value for min is 1e-40
 * 
 * INPUTS :
 * 		double	x	The value to be loged
 * 		double 	mn	Minimum value
 * 
 * RETURNS :
 * 		double	log(x)	Log of x
 * 	
 * ********************************************************************/
double cliplog(double x, double mn);
#endif

#ifndef __RANDOMNUMBER_H__
#define __RANDOMNUMBER_H__
#include <math.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

#endif
using namespace std;

/***********************************************************************
 * NAME : 	void SeedRandom()
 * 
 * DESCRIPTION : 	Seeds the random number generator using the time.
 * 
 * ********************************************************************/
void SeedRandom();

/***********************************************************************
 * NAME : 	int	RandomNumber(Range)
 * 
 * DESCRIPTION : 	Provides random integers within a specified range.
 * 
 * INPUTS : 
 * 		int		*Range		2-element array defining the upper and lower
 * 							limits for the output.
 * 
 * RETURNS : 
 * 		int		RandomNumber	Single random integer
 * 
 * ********************************************************************/
int RandomNumber(int *Range);

/***********************************************************************
 * NAME : 	int	RandomNumber(R0,R1)
 * 
 * DESCRIPTION : 	Provides random integers within a specified range.
 * 
 * INPUTS : 
 * 		int		R0		Lower limit of the output range
 * 		int		R1		Upper limit of the output range
 * 
 * RETURNS : 
 * 		int		RandomNumber	Single random integer
 * 
 * ********************************************************************/
int RandomNumber(int R0, int R1);

/***********************************************************************
 * NAME : 	float RandomNumber(Range)
 * 
 * DESCRIPTION : 	Provides random floats within a specified range.
 * 
 * INPUTS : 
 * 		float 	*Range		2-element array defining the upper and lower
 * 							limits for the output.
 * 
 * RETURNS : 
 * 		float		RandomNumber	Single random float
 * 
 * ********************************************************************/
float RandomNumber(float *Range);

/***********************************************************************
 * NAME : 	float	RandomNumber(R0,R1)
 * 
 * DESCRIPTION : 	Provides random floats within a specified range.
 * 
 * INPUTS : 
 * 		float		R0		Lower limit of the output range
 * 		float		R1		Upper limit of the output range
 * 
 * RETURNS : 
 * 		float		RandomNumber	Single random float
 * 
 * ********************************************************************/
float RandomNumber(float R0, float R1);

/***********************************************************************
 * NAME : 	float	RandomNumber(R0,R1)
 * 
 * DESCRIPTION : 	Provides random floats within a specified 
 * 					logarithmic range.
 * 
 * INPUTS : 
 * 		float		R0		Lower limit of the output range
 * 		float		R1		Upper limit of the output range
 * 
 * RETURNS : 
 * 		float		RandomNumber	Single random float
 * 
 * ********************************************************************/
float RandomLogRange(float R0, float R1);

/***********************************************************************
 * NAME : 	float	RandomNumber(R0,R1)
 * 
 * DESCRIPTION : 	Provides random floats within a specified 
 * 					logarithmic range.
 * 
 * INPUTS : 
 * 		float 	*Range		2-element array defining the upper and lower
 * 							limits for the output.
 * 
 * RETURNS : 
 * 		float		RandomNumber	Single random float
 * 
 * ********************************************************************/
float RandomLogRange(float *Range);


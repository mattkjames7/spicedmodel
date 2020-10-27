#include "randomnumber.h"

/***********************************************************************
 * NAME : 	void SeedRandom()
 * 
 * DESCRIPTION : 	Seeds the random number generator using the time.
 * 
 * ********************************************************************/
void SeedRandom() {
	//seed the random number generator
	srand((unsigned) time(NULL));
}	

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
int RandomNumber(int *Range) {
	//seed the random number generator
	//srand((unsigned) time(NULL));
	
	//now fill each array
	return (int) round((Range[1]-Range[0])*(((float) rand()) / ((float) RAND_MAX))) + Range[0];
}

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
int RandomNumber(int R0, int R1) {
	//seed the random number generator
	//srand((unsigned) time(NULL));
	
	//now fill each array
	return (int) round((R1-R0)*(((float) rand()) / ((float) RAND_MAX))) + R0;
}

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
float RandomNumber(float *Range) {
	//seed the random number generator
	//srand((unsigned) time(NULL));
	
	//now fill each array
	return (Range[1]-Range[0])*(((float) rand()) / ((float) RAND_MAX)) + Range[0];
}

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
float RandomNumber(float R0, float R1) {
	//seed the random number generator
	//srand((unsigned) time(NULL));
	
	//now fill each array
	return (R1-R0)*(((float) rand()) / ((float) RAND_MAX)) + R0;
}

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
float RandomLogRange(float R0, float R1) {
	R0 = log10f(R0);
	R1 = log10f(R1);
	return powf((R1-R0)*(((float) rand()) / ((float) RAND_MAX)) + R0,10.0);
}

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
float RandomLogRange(float *Range) {
	float R0 = log10f(Range[0]);
	float R1 = log10f(Range[1]);
	return powf(10.0,(R1-R0)*(((float) rand()) / ((float) RAND_MAX)) + R0);
}

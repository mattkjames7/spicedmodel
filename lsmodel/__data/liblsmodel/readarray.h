#ifndef __READARRAY_H__
#define __READARRAY_H__
#include <stdio.h>
#include <stdlib.h>

#endif

using namespace std;




/***********************************************************************
 * NAME : 	unsigned char * readArray(p,v,n)
 * 
 * DESCRIPTION : Reads in a 1D floating point array from memory given a 
 * 				pointer.
 * 
 * INPUTS : 
 * 		unsigned char	*p	Pointer to the memory address to start from
 * 		
 * OUTPUTS : 
 * 		float 			*v 	This will contain the array of floats
 * 		int				*n	The number of elements within v
 * 
 * RETURNS : 
 * 		unsigned char	*p	New pointer address
 * 
 * ********************************************************************/
unsigned char * readArray(unsigned char *p, float **v, int *n);

/***********************************************************************
 * NAME : 	unsigned char * readArray(p,v,shape)
 * 
 * DESCRIPTION : Reads in a 2D floating point array from memory given a 
 * 				pointer.
 * 
 * INPUTS : 
 * 		unsigned char	*p	Pointer to the memory address to start from
 * 		
 * OUTPUTS : 
 * 		float 			**v 	This will contain the array of floats
 * 		int				*shape	The number of elements within each 
 * 								dimension of v
 * 
 * RETURNS : 
 * 		unsigned char	*p	New pointer address
 *  
 * ********************************************************************/
unsigned char * readArray(unsigned char *p, float ***v, int *shape);

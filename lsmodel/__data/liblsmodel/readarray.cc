#include "readarray.h"



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
unsigned char * readArray(unsigned char *p, float **v, int *n) {

	/* start by reading the total size of the array */
	n[0] = ((int*) p)[0];
	p += sizeof(int);
	
	/* now read in the number of dimensions (only important for Python
	 * here we assume that this is 1D */
	int ns, shape;
	ns = ((int*) p)[0];
	shape = ((int*) p)[1];
	p += 2*sizeof(int);
	
	/* let's initialize the output pointer */
	*v = new float[n[0]];
	
	/* read in the array */
	int i;
	for (i=0;i<n[0];i++) {
		(*v)[i] = ((float*) p)[0];
		p += sizeof(float);
	}
	
	return p;
	
}


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
unsigned char * readArray(unsigned char *p, float ***v, int *shape) {

	/* start by reading the total size of the array */
	int n;
	n = ((int*) p)[0];
	p += sizeof(int);
	
	/* now read in the number of dimensions (only important for Python
	 * here we assume that this is 2D */
	int ns;
	ns = ((int*) p)[0];
	shape[0] = ((int*) p)[1];
	shape[1] = ((int*) p)[2];
	p += 3*sizeof(int);
		
	/* let's initialize the output pointer */
	*v = new float*[shape[0]];
	int i;
	for (i=0;i<shape[0];i++) {
		(*v)[i] = new float[shape[1]];
	}
	
	/* read in the array */
	int j;
	for (i=0;i<shape[0];i++) {
		for (j=0;j<shape[1];j++) {
			(*v)[i][j] = ((float*) p)[0];
			p += sizeof(float);
		}
	}
	return p;
}

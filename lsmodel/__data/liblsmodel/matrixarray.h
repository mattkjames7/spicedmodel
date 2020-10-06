#ifndef __MATRIXARRAY_H__
#define __MATRIXARRAY_H__
#include <math.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include "matrix.h"
using namespace std;

class MatrixArray {
	public:
		/* constructor of the array */
		MatrixArray(int,int*);
		MatrixArray(unsigned char *memstart);
		
		/* copy constructor */
		MatrixArray(const MatrixArray &obj);
		
		/* destructor */
		~MatrixArray();
		
		/* random initialization of the array contained in this object */
		void RandomInit(float);
		
		/* this is the array of matrices contained within this object */
		int n;
		Matrix **matrix;
	private:

};

#endif

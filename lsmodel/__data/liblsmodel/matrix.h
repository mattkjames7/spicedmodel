#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

class Matrix {
	public:
		/* Initialize matrix with zeros */
		Matrix(int*);
		Matrix(int,int);
		
		/* initialize matrix with existing data */
		Matrix(int*,double**);
		Matrix(int,int,double**);
		
		/* copy constructor */
		Matrix(const Matrix &obj);
	
		/* destructor */
		~Matrix();
		
		/* fill the entire matrix with zeros */
		void FillZeros();
		
		/* multiply each elements by some number */
		void TimesScalar(double);
		
		/* divide each element by a scalar */
		void DivideScalar(double);
		
		/* add each element to a scalar */
		void AddScalar(double);
		
		/* subtract a scalar from each elements */
		void SubtractScalar(double);
		
		/* subtract each element from a scalar */
		void SubtractFromScalar(double);
		
		/* Don't use this with massive arrays*/
		void PrintMatrix();
		void PrintMatrix(const char *);
		
		/* copy another matrix into the current one */
		void CopyMatrix(Matrix&);
		
		/* fill this matrix with the data from another of the same size*/
		void FillMatrix(double**);
		void FillMatrix(float**);
		
		/* return the data from this matrix into a 2D array */
		void ReturnMatrix(double**);
		void ReturnMatrix(float**);
		
		/* this is the data array with its shape and total size*/
		int shape[2];
		int size;
		double **data = NULL;
	private:
		bool DeleteData;
		
};

#endif

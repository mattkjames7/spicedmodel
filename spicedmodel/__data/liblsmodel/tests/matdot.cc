#include "matdot.h"

void testMatDot() {
	
	printf("***********Test Matrix Multiplication Code*********************\n");
	Matrix *ma = new Matrix(2,3);
	Matrix *mb = new Matrix(3,4);
	Matrix *mc = new Matrix(2,4);
	
	ma->data[0][0] = 1.0;
	ma->data[0][1] = 2.0;
	ma->data[0][2] = 3.0;
	ma->data[1][0] = 4.0;
	ma->data[1][1] = 5.0;
	ma->data[1][2] = 6.0;
	
	mb->data[0][0] = 0.1;
	mb->data[0][1] = 0.1;
	mb->data[0][2] = 0.4;
	mb->data[0][3] = 0.2;
	mb->data[1][0] = 0.9;
	mb->data[1][1] = 0.7;
	mb->data[1][2] = 0.1;
	mb->data[1][3] = 0.2;
	mb->data[2][0] = 0.3;
	mb->data[2][1] = 0.5;
	mb->data[2][2] = 0.6;
	mb->data[2][3] = 0.7;


	MatrixDot(*ma,*mb,false,false,*mc);
	
	ma->PrintMatrix("Matrix a:");
	mb->PrintMatrix("Matrix b:");
	mc->PrintMatrix("Matrix c:");
	
}

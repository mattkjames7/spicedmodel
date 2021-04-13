#ifndef __SOFTMAX_H__
#define __SOFTMAX_H__
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
/***********************************************************************
 * NAME : 	void softmax(z,sm)
 * 
 * DESCRIPTION : Calcualtes the softmax function for the last layer of
 * 					a neural network.
 * 
 * INPUTS : 	
 * 		Matrix	z	The output of the final neural network layer before
 * 					any activation function has been applied to it.
 * 
 * OUTPUTS : 
 * 		Matrix	sm	The softmax function output, effectively a 
 * 					probability.
 * 
 * ********************************************************************/
void softmax(Matrix z, Matrix &sm);
#endif

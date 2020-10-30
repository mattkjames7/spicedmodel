#include "test.h"


int main() {
	
	printf("************Testing the average Mav model***************\n");
	/* this will performa  simple test on average ion mass model */
	AvMavModel mav(&_binary_mav_bin_start);

	/*create some positions */
	float R[] = {1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,4.0,4.0,4.0,4.0};
	float mlt[] = {12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,0.0,6.0,12.0,18.0};
	float out[14];
	int i, j;

	/* attempt to calculate the model */
	mav.Model(14,mlt,R,true,false,true,1,3,out);
	
	/* print the result */
	for (i=0;i<14;i++) {
		printf("R: %3.1f MLT: %4.1f mav: %5.2f\n",R[i],mlt[i],out[i]);
	}
	
	printf("************Testing the average Prob model**************\n");
	/* create the prob model instance */
	AvProbModel prob(&_binary_prob_bin_start);
	
	/* calculate the model */
	prob.Model(14,mlt,R,true,false,true,1,3,out);
	
	/* print the result */
	for (i=0;i<14;i++) {
		printf("R: %3.1f MLT: %4.1f prob: %5.2f\n",R[i],mlt[i],out[i]);
	}	
	
	printf("************Testing the average PS model**************\n");
	/* create the prob model instance */
	AvPSModel ps(&_binary_ps_bin_start);
	
	/* calculate the model */
	ps.Model(14,mlt,R,true,false,true,1,3,true,out);
	
	/* print the result */
	for (i=0;i<14;i++) {
		printf("R: %3.1f MLT: %4.1f ps: %5.2f\n",R[i],mlt[i],out[i]);
	}	
	
	printf("************Testing the average PT model**************\n");
	/* create the prob model instance */
	AvPTModel pt(&_binary_pt_bin_start);
	
	/* calculate the model */
	pt.Model(14,mlt,R,true,false,true,1,3,true,out);
	
	/* print the result */
	for (i=0;i<14;i++) {
		printf("R: %3.1f MLT: %4.1f pt: %5.2f\n",R[i],mlt[i],out[i]);
	}	
	
	
	printf("***********Test reading ANN file*********************\n");
	/* read the mavann.bin data from memory */
	
	/* create a local copy of the pointer */
	unsigned char *p = &_binary_mavann_bin_start;
	
	
	/* Read in s first (also L) */
	int L;
	int *s;
	p = readArray(p,&s,&L);
	printf("ANN layers:\n");
	for (i=0;i<L;i++) {
		printf("Layer %d: %d nodes\n",i,s[i]);
	}
	delete s;
	
	/* read in the rescaling parameters */
	int itmp;
	float *scale0, *scale1;
	printf("Scale factors:\n");
	p = readArray(p,&scale0,&itmp);
	p = readArray(p,&scale1,&itmp);
	printf("  Scale0  |  Scale1 \n");
	printf("---------------------\n");
	for (i=0;i<itmp;i++) {
		printf("%9.5f | %9.5f\n",scale0[i],scale1[i]);
	}
	delete scale0;
	delete scale1;


	/* now read in the matrices */
	MatrixArray *W, *B;
	printf("Weight matrices:\n");
	W = new MatrixArray(&p);
	for (i=0;i<W->n;i++) {
		printf("Matrix %d: (%d,%d)\n",i,W->matrix[i]->shape[0],W->matrix[i]->shape[1]);
	}
	printf("Deleting matrix array\n");
	delete W;
	
	printf("Bias matrices:\n");
	B = new MatrixArray(&p);
	for (i=0;i<B->n;i++) {
		printf("Matrix %d: (%d,%d)\n",i,B->matrix[i]->shape[0],B->matrix[i]->shape[1]);
	}
	printf("Deleting matrix array\n");
	delete B;

	/* now read the cost functions */
	printf("Training Cost:\n");
	int nEpoch;
	float *Jt, *Jc;
	p = readArray(p,&Jt,&nEpoch);
	printf("%d Epochs\n",nEpoch);
	
	printf("Validation Cost:\n");
	p = readArray(p,&Jc,&nEpoch);
	printf("%d Epochs\n",nEpoch);
	
	delete Jt;
	delete Jc;
	
	
	
	
	printf("***********Test Matrix Code*********************\n");
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
	
	
	printf("***********Test creating ANN object*********************\n");
	NetworkFunc *ann = new NetworkFunc(&_binary_mavann_bin_start,"softplus","linear","mean_squared");
	
	/* invent some weights and biases */
	int st[] = {3,2,1};
	int Lt = 3;
	NetworkFunc *annt = new NetworkFunc(Lt,st,"softplus","linear","mean_square");
	annt->W_->matrix[0]->data[0][0] = 0.0;
	annt->W_->matrix[0]->data[1][0] = 0.1;
	annt->W_->matrix[0]->data[2][0] = 0.3;
	annt->W_->matrix[0]->data[0][1] = 0.5;
	annt->W_->matrix[0]->data[1][1] = 0.2;
	annt->W_->matrix[0]->data[2][1] = 0.4;

	annt->W_->matrix[1]->data[0][0] = 0.3;
	annt->W_->matrix[1]->data[1][0] = 0.1;	
	
	
	annt->B_->matrix[0]->data[0][0] = 0.1;	
	annt->B_->matrix[0]->data[0][1] = 0.2;	
	
	annt->B_->matrix[1]->data[0][0] = 0.3;	
	
	/* create an input and output matrix */
	float **in, **aout;
	in = new float*[2];
	in[0] = new float[3];
	in[1] = new float[3];
	
	in[0][0] = 1.0;
	in[0][1] = 1.0;
	in[0][2] = 1.0;
	in[1][0] = 2.0;
	in[1][1] = 2.0;
	in[1][2] = 2.0;
	
	aout = new float*[2];
	aout[0] = new float[1];
	aout[1] = new float[1];
	annt->Predict(2,in,aout);
	
	for (i=0;i<2;i++) {
		printf("%8.6f \n",aout[i][0]);
	}
	
	/* create some test values - rescale them as in the python code */
	float Rt[] = {3.0,4.0,5.0};
	float f107[] = {100.0,110.0,120.0};
	float **anin, **anout;
	anin = new float*[3];
	anout = new float*[3];
	printf("  Rs   |  F107s  \n");
	printf("-----------------\n");
	for (i=0;i<3;i++) {
		anin[i] = new float[7];
		anout[i] = new float[7];
		anin[i][0] = rescaleR(Rt[i]);
		anin[i][1] = rescaleF107(f107[i]);
		printf(" %5.2f | %6.3f \n",anin[i][0],anin[i][1]);
	}
	
	/* try predicting the output */
	printf("Predict the model components\n");
	ann->Predict(3,anin,anout);
	
	/* print out */
	printf("Model Components\n");
	printf("DC    |     R0   |     R1   |     R2   |     I0   |     I1   |     I2 \n");
	printf("----------------------------------------------------------------------\n");
	for (i=0;i<3;i++) {
		printf("%5.2f",anout[i][0]);
		for (j=1;j<7;j++) {
			printf(" | %8.5f",anout[i][j]);
		}
		printf("\n"); 
	}
	printf("Delete ANN object\n");
	delete annt;
	for (i=0;i<2;i++) {
		delete[] anin[i];
		delete[] anout[i];
	}
	delete[] anin;
	delete[] anout;
	
	
	printf("***********Test Mav ANN object*********************\n");
	ANNMavModel *mavann = new ANNMavModel(&_binary_mavann_bin_start);
	
	/* create some test values */
	float Rann[] = {1.0,1.0,3.0,3.0,5.0,5.0};
	float Mann[] = {12.0,12.0,12.0,12.0,12.0,12.0}
	float 
	printf("Delete Mav ANN\n");
	delete mavann;
}

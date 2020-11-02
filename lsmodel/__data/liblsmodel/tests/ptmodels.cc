#include "ptmodels.h"

void testPTModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float SMR[] = {0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0};
	float expav[] = {NAN,NAN,87.52281,87.52281,12.565765,12.565765, 
					106.17181,106.17181,9.324627,9.324627};
	float expann[] = {NAN,NAN,104.87785,62.84493,14.667002,11.64771,
					189.02615,55.981377,8.946179,3.5678644};
	float out[10];

	printf("***********Test Average PT object*********************\n");
	AvPTModel *av = new AvPTModel(&_binary_pt_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,true,out);
	
	int i;
	printf("  M  |  R  |   PT   | Expected\n");
	printf("-------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %6.2f | %6.2f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test PT ANN object*********************\n");
	/* create the ann model object */
	ANNPTModel *ann = new ANNPTModel(&_binary_ptann_bin_start);
	
	ann->Model(10,M,R,SMR,true,false,true,1,3,true,out);
	
	printf("  M  |  R  |  SMR  |   PT   | Expected\n");
	printf("---------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.1f | %6.2f | %6.2f\n",M[i],R[i],SMR[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

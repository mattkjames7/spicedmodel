#include "probmodels.h"

void testProbModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float SMR[] = {0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0};
	float expav[] = {NAN,NAN,0.93885595,0.93885595,0.69902945,
					0.69902945,0.95432794,0.95432794,0.7166161,0.7166161};
	float expann[] = {NAN,NAN,1.0,0.37598833,0.78744745,
						0.3163298,1.0,0.2835528,0.8313806,0.0};
	float out[10];

	printf("***********Test Average Prob object*********************\n");
	AvProbModel *av = new AvProbModel(&_binary_prob_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,out);
	
	int i;
	printf("  M  |  R  |  Prob | Expected\n");
	printf("------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.3f | %5.3f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test Prob ANN object*********************\n");
	/* create the ann model object */
	ANNProbModel *ann = new ANNProbModel(&_binary_probann_bin_start);
	
	ann->Model(10,M,R,SMR,true,false,true,1,3,out);
	
	printf("  M  |  R  |  SMR  |  Prob | Expected\n");
	printf("--------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.1f | %5.3f | %5.3f\n",M[i],R[i],SMR[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

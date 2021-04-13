#include "psmodels.h"

void testPSModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float SMR[] = {0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0};
	float expav[] = {NAN,NAN,990.28314,990.28314,148.69296,148.69296, 
					1032.8657,1032.8657,151.89738,151.89738};
	float expann[] = {NAN,NAN,1061.2566,976.14343,137.02544,
						164.9483,1166.6492,849.7204,145.7129,125.961174};
	float out[10];

	printf("***********Test Average PS object*********************\n");
	AvPSModel *av = new AvPSModel(&_binary_ps_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,true,out);
	
	int i;
	printf("  M  |  R  |    PS   | Expected\n");
	printf("------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %7.2f | %7.2f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test PS ANN object*********************\n");
	/* create the ann model object */
	ANNPSModel *ann = new ANNPSModel(&_binary_psann_bin_start);
	
	ann->Model(10,M,R,SMR,true,false,true,1,3,true,out);
	
	printf("  M  |  R  |  SMR  |    PS   | Expected\n");
	printf("--------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.1f | %7.2f | %7.2f\n",M[i],R[i],SMR[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

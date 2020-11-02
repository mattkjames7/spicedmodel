#include "mavmodels.h"

void testMavModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float f107[] = {80.0,150.0,80.0,150.0,80.0,150.0,80.0,150.0,80.0,150.0,};
	float expav[] = {NAN,NAN,12.318951,12.318951,5.4738965,5.4738965, 
					13.072797,13.072797,5.1035433,5.1035433};
	float expann[] = {NAN,NAN,11.570872,13.486695,4.463351,7.5160146,
					12.105549,13.816255,4.301272,6.5384946};
	float out[10];

	printf("***********Test Average Mav object*********************\n");
	AvMavModel *av = new AvMavModel(&_binary_mav_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,out);
	
	int i;
	printf("  M  |  R  |  Mav  | Expected\n");
	printf("------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.2f | %5.2f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test Mav ANN object*********************\n");
	/* create the ann model object */
	ANNMavModel *ann = new ANNMavModel(&_binary_mavann_bin_start);
	
	ann->Model(10,M,R,f107,true,false,true,1,3,out);
	
	printf("  M  |  R  |  F10.7  |  Mav  | Expected\n");
	printf("--------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f |  %5.1f  | %5.2f | %5.2f\n",M[i],R[i],f107[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

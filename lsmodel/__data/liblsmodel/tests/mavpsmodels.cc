#include "mavpsmodels.h"

void testMavPSModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float smr[] = {0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0};
	float expav[] = {NAN,NAN,1.3968269, 1.3968269, 2.1019368, 2.1019368,
				1.4696023, 1.4696023, 1.980714 , 1.980714};
	float expann[] = {NAN,NAN,1.3592811, 1.485725 , 2.301059 , 2.5518396,
			1.5020472, 1.6109227, 1.8444198, 2.7693517};
	float out[10];

	printf("***********Test Average MavPS object*********************\n");
	AvMavPSModel *av = new AvMavPSModel(&_binary_mavcps_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,true,out);
	
	int i;
	printf("  M  |  R  | MavPS | Expected\n");
	printf("------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.2f | %5.2f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test MavPS ANN object*********************\n");
	/* create the ann model object */
	ANNMavPSModel *ann = new ANNMavPSModel(&_binary_mavcpsann_bin_start);
	
	ann->Model(10,M,R,smr,true,false,true,1,3,true,out);
	
	printf("  M  |  R  |   SMR   | MavPS | Expected\n");
	printf("--------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f |  %5.1f  | %5.2f | %5.2f\n",M[i],R[i],smr[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

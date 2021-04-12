#include "mavptmodels.h"

void testMavPTModels() {

	/* create some test values */
	float R[] = {1.0,1.0,3.0,3.0,5.0,5.0,3.0,3.0,5.0,5.0};
	float M[] = {12.0,12.0,12.0,12.0,12.0,12.0,6.0,6.0,6.0,6.0};
	float smr[] = {0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0,0.0,-70.0};
	float expav[] = {NAN,NAN,1.9504597, 1.9504597, 2.6499078, 2.6499078,
			2.1929426, 2.1929426, 3.029526 , 3.029526};
	float expann[] = {NAN,NAN,1.7939754, 1.899296 , 2.5001588, 3.7644882,
			1.852312 , 2.4547524, 3.2158868, 5.6342287};
	float out[10];

	printf("***********Test Average MavPT object*********************\n");
	AvMavPTModel *av = new AvMavPTModel(&_binary_mavcpt_bin_start);
	
	av->Model(10,M,R,true,false,true,1,3,true,out);
	
	int i;
	printf("  M  |  R  | MavPT | Expected\n");
	printf("------------------------------\n");
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f | %5.2f | %5.2f\n",M[i],R[i],out[i],expav[i]);
	}

	printf("Delete object\n");
	delete av;

	printf("***********Test MavPT ANN object*********************\n");
	/* create the ann model object */
	ANNMavPTModel *ann = new ANNMavPTModel(&_binary_mavcptann_bin_start);
	
	ann->Model(10,M,R,smr,true,false,true,1,3,true,out);
	
	printf("  M  |  R  |   SMR   | MavPT | Expected\n");
	printf("--------------------------------------\n");	
	for (i=0;i<10;i++) {
		printf("%4.1f | %3.1f |  %5.1f  | %5.2f | %5.2f\n",M[i],R[i],smr[i],out[i],expann[i]);
	}
	
	
	printf("Delete object\n");
	delete ann;


}

#include "testmavtrans.h"

/***********************************************************************
 * Perform a few basic tests to see if MavTrans works the way it does
 * in Python.
 * ********************************************************************/
void testMavTrans() {
	
	int n = 8;
	float r[] = {2.0,2.0,3.0,3.0,4.0,4.0,5.0,5.0};
	float m[] = {2.0,5.0,2.0,5.0,2.0,5.0,2.0,5.0};
	float mtps[8], mtpt[8], mps[8], mpt[8];
	float mtpspy[] = {0.47947973, 0.7380855 , 0.28179038, 0.3156063 , 0.31757033,  0.3726183 , 0.5091318 , 0.8288679 };
	float mtptpy[] = {0.494816  , 0.78397655, 0.5080598 , 0.8254361 , 0.51894397,  0.8608151 , 0.6200251 , 1.2505854};
	
	/*load the transform object */
	MavTrans *MT = new MavTrans();
	
	
	/*transform forward*/
	MT->PSTransform(n,r,m,mtps);
	MT->PTTransform(n,r,m,mtpt);
	
	/*and back*/
	MT->PSRevTransform(n,r,mtps,mps);
	MT->PTRevTransform(n,r,mtpt,mpt);	
	
	/*compare results*/
	int i;
	printf("PS:\n");
	printf(" R  |  m  |   mtpy    |    mt     |  m  \n");
	printf("----------------------------------------\n");
 	for (i=0;i<n;i++) {
		printf("%3.1f | %3.1f | %9.7f | %9.7f | %3.1f \n",r[i],m[i],mtpspy[i],mtps[i],mps[i]);
	}
	printf("PT:\n");
	printf(" R  |  m  |   mtpy    |    mt     |  m  \n");
	printf("----------------------------------------\n");
	for (i=0;i<n;i++) {
		printf("%3.1f | %3.1f | %9.7f | %9.7f | %3.1f \n",r[i],m[i],mtptpy[i],mtpt[i],mpt[i]);
	}
	delete MT;
}

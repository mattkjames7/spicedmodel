#include "netfunc.h"

void testNetworkFunc() {
	
	printf("***********Test creating ANN object*********************\n");
	NetworkFunc *ann = new NetworkFunc(&_binary_mavhann_bin_start,"softplus","linear","mean_squared");
	int i, j;
	/* create some test values - rescale them as in the python code */
	float R[] = {3.0,4.0,5.0};
	float f107[] = {100.0,110.0,120.0};
	float exp[3][7] = {{1.2105584e+01,1.6899067e-01,7.8518517e-02,-2.7936012e-02,-5.1193756e-01,-9.1861486e-03,6.0065776e-02},
						{8.607196,-0.0330897,0.0917391,-0.06780973,-0.2998723,0.00932938,0.04171638},
						{5.779167,-0.35612214,0.15052514,-0.1549341,-0.09519117,-0.00899297,0.02072102}};
	float **anin, **anout;
	anin = new float*[3];
	anout = new float*[3];
	printf("   R   |  Rs   |  F10.7  |  F10.7s  \n");
	printf("------------------------------------\n");
	for (i=0;i<3;i++) {
		anin[i] = new float[7];
		anout[i] = new float[7];
		anin[i][0] = rescaleR(R[i]);
		anin[i][1] = rescaleF107(f107[i]);
		printf(" %5.2f | %5.2f | %6.3f | %6.3f \n",R[i],anin[i][0],f107[i],anin[i][1]);
	}
	
	/* try predicting the output */
	printf("Predict the model components\n");
	ann->Predict(3,anin,anout);
	
	/* print out */
	printf("Model Components\n");
	printf("DC    |     R0   |     R1   |     R2   |     I0   |     I1   |     I2 \n");
	printf("------------------------------------------------------------------------\n");
	for (i=0;i<3;i++) {
		printf("%5.2f",anout[i][0]);
		for (j=1;j<7;j++) {
			printf(" | %8.5f",anout[i][j]);
		}
		printf("\n"); 
	}
	printf("Expected Components\n");
	printf("DC    |     R0   |     R1   |     R2   |     I0   |     I1   |     I2 \n");
	printf("------------------------------------------------------------------------\n");
	for (i=0;i<3;i++) {
		printf("%5.2f",exp[i][0]);
		for (j=1;j<7;j++) {
			printf(" | %8.5f",exp[i][j]);
		}
		printf("\n"); 
	}
	printf("Delete ANN object\n");
	for (i=0;i<2;i++) {
		delete[] anin[i];
		delete[] anout[i];
	}
	delete[] anin;
	delete[] anout;	
	
}

#include "test.h"


int main() {
	
	/* this will performa  simple test on average ion mass model */
	AvMavModel mav(&_binary_mav_bin_start);

	/*create some positions */
	float R[] = {1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,4.0,4.0,4.0,4.0};
	float mlt[] = {12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,12.0,0.0,6.0,12.0,18.0};
	float out[14];
	int i;

	/* attempt to calculate the model */
	mav.Model(14,mlt,R,true,false,true,1,3,out);
	
	/* print the result */
	for (i=0;i<14;i++) {
		printf("R: %3.1f MLT: %4.1f mav: %5.2f\n",R[i],mlt[i],out[i]);
	}
	
	
}

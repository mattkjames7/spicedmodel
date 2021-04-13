#include "annmavhmodel.h"

/***********************************************************************
 * NAME : ANNMavHModel(ptr)
 * 
 * DESCRIPTION : Constructor of the ANNMavHModel object. This is for
 * 			hot ions!!!
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
ANNMavHModel::ANNMavHModel(unsigned char *ptr) {
	
	/* I think that we just need to read the model in and load the
	 * ANNModel object */
	LoadANN(ptr);
	
	
}

/***********************************************************************
 * NAME : ~ANNMavHModel()
 * 
 * DESCRIPTION :Destructor for the ANNMavHModel object
 * 
 * 
 * ********************************************************************/
ANNMavHModel::~ANNMavHModel() {
	
	/* here we need to free up the model parameters */
	int i;
	delete[] m_;
	delete[] wl_;
	delete ann_;
	
}


/***********************************************************************
 * NAME : void ModelCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : Calculates the model at a number of Cartesian x and y
 * 				positions.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*x			SM x-coordinate
 * 		float 	*y			SM y-coordinate
 * 		float	*f107		The F10.7 index
 * 		bool	ShowDC		If true then the DC component will be included
 * 		bool	OnlyDC		If true ONLY the DC component will be included
 * 		bool	Validate	If true, then all elements will be checked
 * 							to make sure that they are within the 
 * 							accepted L-shell range (2 to 5.9 Re) and
 * 							that the values are within the possible
 * 							m_av range(1.0 to 16.0 amu)
 * 		int		m0			The starting m number to include
 * 		int		m1			The final m number to include
 * 
 * OUTPUTS : 
 * 		float	*out		The model average ion mass
 * 
 * 
 * ********************************************************************/
void ANNMavHModel::ModelCart(int n, float *x, float *y, float *f107,
							bool ShowDC, bool OnlyDC, bool Validate, 
							int m0, int m1, float *out) {
				
	/* convert x and y to mlt and R */
	float *mlt = new float[n];
	float *R = new float[n];
	CartMLTR(n,x,y,mlt,R);
	
	/* call the model function */
	Model(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out);
		
	/* clean up */
	delete[] mlt;
	delete[] R;
}

/***********************************************************************
 * NAME : void Model(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : Calculates the model at a number of positions in MLT 
 * 				and R.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*mlt		Magnetic local time
 * 		float 	*R			The radial distance (L-shell)
 * 		float	*f107		The F10.7 index
 * 		bool	ShowDC		If true then the DC component will be included
 * 		bool	OnlyDC		If true ONLY the DC component will be included
 * 		bool	Validate	If true, then all elements will be checked
 * 							to make sure that they are within the 
 * 							accepted L-shell range (2 to 5.9 Re) and
 * 							that the values are within the possible
 * 							m_av range(1.0 to 16.0 amu)
 * 		int		m0			The starting m number to include
 * 		int		m1			The final m number to include
 * 
 * OUTPUTS : 
 * 		float	*out		The model average ion mass
 * 
 * 
 * ********************************************************************/
void ANNMavHModel::Model(int n, float *mlt, float *R, float *f107,
						bool ShowDC, bool OnlyDC,bool Validate, 
						int m0, int m1, float *out){
	
	/* create the arrays to store dc and periodic components of the model */
	int i, j;
	float *dc = new float[n];
	float **per = new float*[nm_];
	for (i=0;i<nm_;i++) {
		per[i] = new float[n];
	}
	
	/* rescale F10.7 */
	float *f107s =  new float[n];
	for (i=0;i<n;i++) {
		f107s[i] = rescaleF107(f107[i]);
	}
	
	/* now let's get the model components */
	ModelComponents(n,mlt,R,f107s,dc,per);

	/* Add the DC component if we are including this in the output */
	if (OnlyDC || ShowDC) {
		/* add the DC component */
		for (i=0;i<n;i++) {
			out[i] = dc[i];
		}
	} else { 
		/* fill with zeros */
		for (i=0;i<n;i++) {
			out[i] = 0.0;
		}
	}

	/* if we are not just returning the DC component, we need to think 
	 * about the periodic bits of the model */
	if (!OnlyDC) {
		/* work out which components we will include based on m0 and m1*/
		int i0, i1;
		i0 = max(0,m0-1);
		i1 = min(nm_-1,m1-1);
		
		/* now add them to the existing array */
		for (i=i0;i<=i1;i++) {
			for (j=0;j<n;j++) {
				out[j] += per[i][j];
			}
		}
	}

	/* make sure that we remove anything invalid*/
	if (Validate) {
		for (i=0;i<n;i++) {
			if ((R[i] > 5.9) || (R[i] < 2.0)) {
				/* outside of the model L-shell range */
				out[i] = NAN;
			} else if ((out[i] > 16.0) && (ShowDC)) {
				/* shouldn't be more than 16.0 */
				out[i] = 16.0;
			} else if ((out[i] < 1.0) && (ShowDC)) {
				/* not physically possible to be below 1.0 */
				out[i] = 1.0;
			}
		}
	}
	
	/* clean up */
	delete[] dc;
	for (i=0;i<nm_;i++) {
		delete[] per[i];
	}
	delete[] per;
	delete [] f107s;
		
}





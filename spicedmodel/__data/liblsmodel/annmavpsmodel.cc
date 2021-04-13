#include "annmavpsmodel.h"

/***********************************************************************
 * NAME : ANNMavPSModel(ptr)
 * 
 * DESCRIPTION : Constructor of the ANNMavPSModel object.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
ANNMavPSModel::ANNMavPSModel(unsigned char *ptr) {
	
	/* I think that we just need to read the model in and load the
	 * ANNModel object */
	LoadANN(ptr);
	
	
	/* Finally store an object which can transform the mav values*/
	MT_ = new MavTrans();	
	
}

/***********************************************************************
 * NAME : ~ANNMavPSModel()
 * 
 * DESCRIPTION :Destructor for the ANNMavPSModel object
 * 
 * 
 * ********************************************************************/
ANNMavPSModel::~ANNMavPSModel() {
	
	/* here we need to free up the model parameters */
	int i;
	delete[] m_;
	delete[] wl_;
	delete ann_;

	delete MT_;	
}


/***********************************************************************
 * NAME : void ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : Calculates the model at a number of Cartesian x and y
 * 				positions.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*x			SM x-coordinate
 * 		float 	*y			SM y-coordinate
 * 		float	*smr		The SMR index
 * 		bool	ShowDC		If true then the DC component will be included
 * 		bool	OnlyDC		If true ONLY the DC component will be included
 * 		bool	Validate	If true, then all elements will be checked
 * 							to make sure that they are within the 
 * 							accepted L-shell range (2 to 5.9 Re) and
 * 							that the values are within the possible
 * 							m_av range(1.0 to 16.0 amu)
 * 		int		m0			The starting m number to include
 * 		int		m1			The final m number to include
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS : 
 * 		float	*out		The model average ion mass
 * 
 * 
 * ********************************************************************/
void ANNMavPSModel::ModelCart(int n, float *x, float *y, float *smr,
							bool ShowDC, bool OnlyDC, bool Validate, 
							int m0, int m1, bool RevTrans, float *out) {
				
	/* convert x and y to mlt and R */
	float *mlt = new float[n];
	float *R = new float[n];
	CartMLTR(n,x,y,mlt,R);
	
	/* call the model function */
	Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
		
	/* clean up */
	delete[] mlt;
	delete[] R;
}

/***********************************************************************
 * NAME : void Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : Calculates the model at a number of positions in MLT 
 * 				and R.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*mlt		Magnetic local time
 * 		float 	*R			The radial distance (L-shell)
 * 		float	*smr		The SMR index
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
void ANNMavPSModel::Model(int n, float *mlt, float *R, float *smr,
						bool ShowDC, bool OnlyDC,bool Validate, 
						int m0, int m1, bool RevTrans, float *out){
	
	/* create the arrays to store dc and periodic components of the model */
	int i, j;
	float *dc = new float[n];
	float **per = new float*[nm_];
	for (i=0;i<nm_;i++) {
		per[i] = new float[n];
	}
	
	/* rescale F10.7 */
	float *smrs =  new float[n];
	for (i=0;i<n;i++) {
		smrs[i] = rescaleSMR(smr[i]);
	}
	
	/* now let's get the model components */
	ModelComponents(n,mlt,R,smrs,dc,per);

	/* add the DC component */
	for (i=0;i<n;i++) {
		out[i] = dc[i];
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

	/*reverse transform*/
	if (RevTrans) {
		MT_->PSRevTransform(n,R,out,out);
		MT_->PSRevTransform(n,R,dc,dc);
	}

	/* remove the DC component if we need to */
	if ((!OnlyDC) && (!ShowDC)) {
		for (i=0;i<n;i++) {
			out[i] = out[i] - dc[i];
		}
	}
	
	/* make sure that we remove anything invalid*/
	if (Validate) {
		for (i=0;i<n;i++) {
			if ((R[i] > 5.9) || (R[i] < 2.0)) {
				/* outside of the model L-shell range */
				out[i] = NAN;
			} else if ((out[i] > 16.0) && (ShowDC) && (RevTrans)) {
				/* shouldn't be more than 16.0 */
				out[i] = 16.0;
			} else if ((out[i] < 1.0) && (ShowDC) && (RevTrans)) {
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
	delete [] smrs;
		
}





#include "annpsmodel.h"

/***********************************************************************
 * NAME : ANNPSModel(ptr)
 * 
 * DESCRIPTION : Constructor of the ANNPSModel object.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
ANNPSModel::ANNPSModel(unsigned char *ptr) {
	
	/* I think that we just need to read the model in and load the
	 * ANNModel object */
	LoadANN(ptr);
	
	
}

/***********************************************************************
 * NAME : ~ANNPSModel()
 * 
 * DESCRIPTION :Destructor for the ANNPSModel object
 * 
 * 
 * ********************************************************************/
ANNPSModel::~ANNPSModel() {
	
	/* here we need to free up the model parameters */
	int i;
	delete[] m_;
	delete[] wl_;
	delete ann_;
	
}


/***********************************************************************
 * NAME : void ModelCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
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
 * 
 * OUTPUTS : 
 * 		float	*out		The plasmasphere electron density.
 * 
 * 
 * ********************************************************************/
void ANNPSModel::ModelCart(int n, float *x, float *y, float *smr,
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
 * NAME : void Model(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
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
 * 		float	*out		The plasmasphere electron density.
 * 
 * 
 * ********************************************************************/
void ANNPSModel::Model(int n, float *mlt, float *R, float *smr, 
						bool ShowDC, bool OnlyDC, bool Validate, 
						int m0, int m1, bool RevTrans, float *out){
	
	/* create the arrays to store dc and periodic components of the model */
	int i, j;
	float *dc = new float[n];
	float **per = new float*[nm_];
	for (i=0;i<nm_;i++) {
		per[i] = new float[n];
	}
	
	/* rescale SMR */
	float *smrs =  new float[n];
	for (i=0;i<n;i++) {
		smrs[i] = rescaleSMR(smr[i]);
	}
	
	/* now let's get the model components */
	ModelComponents(n,mlt,R,smrs,dc,per);

	/* add the DC component */
	for (i=0;i<n;i++) {
		out[i] = dc[i];
		//printf("%f\n",dc[i]);
		//printf("%f\n",per[0][i]);
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

	/* reverse the transform */
	float shift = 0.0;
	float lambda = 0.06542969;
	if (RevTrans) {
		for (i=0;i<n;i++) {
			out[i] = unscaleDensity(out[i]);
			dc[i] = unscaleDensity(dc[i]);
		}
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





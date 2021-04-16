#include "avmavpsmodel.h"


/***********************************************************************
 * NAME : AvMavPSModel(ptr)
 * 
 * DESCRIPTION : Constructor of the AvMavPSModel object.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
AvMavPSModel::AvMavPSModel(unsigned char *ptr) {
	
	/* all we need to do is initialize the object by reading in the 
	 * model parameters from the provided memory address */
	ReadModelParams(ptr);
	
	/* we could also do with storing the m-numbers and equivalent
	 * wave lengths */
	nm_ = min(Rshape_[0],Ishape_[0]);
	int i;

	m_ = new int[nm_];
	wl_ = new float[nm_];

	for (i=1;i<=nm_;i++) {
		m_[i-1] = i;
		wl_[i-1] = ((float) i)/24.0;
	}
	
	/* reverse DC for this model */
	reverseArray(ndc_,dc_);
	
	/* Finally store an object which can transform the mav values*/
	MT_ = new MavTrans();
}

/***********************************************************************
 * NAME : ~AvMavPSModel()
 * 
 * DESCRIPTION :Destructor for the AvMavModel object
 * 
 * 
 * ********************************************************************/
AvMavPSModel::~AvMavPSModel() {
	
	/* here we need to free up the model parameters */
	int i;
	delete[] dc_;
	for (i=0;i<Rshape_[0];i++) {
		delete[] R_[i];
	}
	delete[] R_;
	for (i=0;i<Ishape_[0];i++) {
		delete[] I_[i];
	}
	delete[] I_;
	
	/* and the m-numbers */
	delete[] m_;
	delete[] wl_;
	
	delete MT_;
	
}

/***********************************************************************
 * NAME : void DC()
 * 
 * DESCRIPTION : Calculates the DC component of the model.
 * 
 * INPUTS : 
 * 		int		n		The number of elements
 * 		float 	*R		The radial distance (L-shell)
 * 
 * OUTPUTS : 
 * 		float	*dc		The output DC component of the model
 * 
 * 
 * ********************************************************************/
void AvMavPSModel::DC(int n, float *R, float *dc) {

	polynomial(ndc_,dc_,n,R,dc);
	MT_->PSTransform(n,R,dc,dc);
}

/***********************************************************************
 * NAME : void ModelCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : Calculates the model at a number of Cartesian x and y
 * 				positions.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*x			SM x-coordinate
 * 		float 	*y			SM y-coordinate
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
void AvMavPSModel::ModelCart(int n, float *x, float *y, 
							bool ShowDC, bool OnlyDC, bool Validate, 
							int m0, int m1, bool RevTrans, float *out) {
				
	/* convert x and y to mlt and R */
	float *mlt = new float[n];
	float *R = new float[n];
	CartMLTR(n,x,y,mlt,R);
	
	/* call the model function */
	Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out);
		
	/* clean up */
	delete[] mlt;
	delete[] R;
}

/***********************************************************************
 * NAME : void Model(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : Calculates the model at a number of positions in MLT 
 * 				and R.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*mlt		Magnetic local time
 * 		float 	*R			The radial distance (L-shell)
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
void AvMavPSModel::Model(int n, float *mlt, float *R, 
						bool ShowDC, bool OnlyDC, bool Validate, 
						int m0, int m1, bool RevTrans, float *out){
	
	/* create the arrays to store dc and periodic components of the model */
	int i, j;
	float *dc = new float[n];
	float **per = new float*[nm_];
	for (i=0;i<nm_;i++) {
		per[i] = new float[n];
	}

	/* now let's get the model components */
	ModelComponents(n,mlt,R,dc,per);

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
			if ((R[i] > 5.9) || (R[i] < 1.5)) {
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

		
}


/***********************************************************************
 * NAME : void ModelComponents(n,mlt,R,dc,per)
 * 
 * DESCRIPTION : Calculates the individual model components at a number 
 * 				of positions in MLT and R.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*mlt		Magnetic local time
 * 		float 	*R			The radial distance (L-shell)
 * 
 * OUTPUTS : 
 * 		float	*dc			The DC component of the model
 * 		float 	**per		The periodic components of the model, shape
 * 							(nm_,n) - where nm_ is the number of 
 * 							m-numbers supported.
 * 
 * 
 * ********************************************************************/
void AvMavPSModel::ModelComponents(int n, float *mlt, float *R, 
								float *dc, float **per) {

	/* get the DC bit of the model */
	DC(n,R,dc);

	/* now get the periodic componented of the model */
	PeriodicComponents(n,mlt,R,per);

} 

/***********************************************************************
 * NAME : void ModelComponentsCart(n,x,y,dc,per)
 * 
 * DESCRIPTION : Calculates the individual model components at a number 
 * 				of Cartisian positions x and y.
 * 
 * INPUTS : 
 * 		int		n			The number of elements
 * 		float	*x			SM x-coordinate
 * 		float 	*y			SM y-coordinate
 * 
 * OUTPUTS : 
 * 		float	*dc			The DC component of the model
 * 		float 	**per		The periodic components of the model, shape
 * 							(nm_,n) - where nm_ is the number of 
 * 							m-numbers supported.
 * 
 * 
 * ********************************************************************/
void AvMavPSModel::ModelComponentsCart(int n, float *x, float *y, 
									float *dc, float **per) {
	
	/* convert x and y to mlt and R */
	float *mlt = new float[n];
	float *R = new float[n];
	CartMLTR(n,x,y,mlt,R);
	
	/* call the model functions */
	ModelComponents(n,mlt,R,dc,per);
		
	/* clean up */
	delete [] mlt;
	delete [] R;
}

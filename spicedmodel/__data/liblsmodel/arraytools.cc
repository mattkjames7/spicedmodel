
/***********************************************************************
 * NAME	: 		T* createArray(a,n)
 * 
 * DESCRIPTION : 	Template function to create an array of length n
 * 					given a pointer *a.
 * 
 * INPUTS : 
 * 		T	*a		Pointer to new array.
 * 		int	n		Length of the array.
 * 
 * RETURNS : 
 * 		T	*a		Pointer to the new array
 * 
 * ********************************************************************/
template <class T> T* createArray(T *a, int n) {
	T *tmp = new T[n];
	return tmp;
}

/***********************************************************************
 * NAME	: 		void destroyArray(a)
 * 
 * DESCRIPTION : 	Template function to destroy a 1D array
 * 
 * INPUTS : 
 * 		T	*a		Pointer to the array
 * 
 * ********************************************************************/
template <class T> void destroyArray(T *a) {
	delete[] a;
}

/***********************************************************************
 * NAME	: 		T* create2DArray(a,n0,n1)
 * 
 * DESCRIPTION : 	Template function to create an array with dimensions
 * 					(n0,n1) given a pointer **a.
 * 
 * INPUTS : 
 * 		T	**a		Pointer to new array.
 * 		int	n0		Length of the 1st dimension of the array.
 * 		int	n1		Length of the 2nd dimension of the array.
 * 
 * RETURNS : 
 * 		T	**a		Pointer to the new array
 * 
 * ********************************************************************/
template <class T> T** create2DArray(T **a, int n0, int n1) {
	T **tmp = new T*[n0];
	int i;
	for (i=0;i<n0;i++) {
		tmp[i] = new T[n1];
	}
	return tmp;
}

/***********************************************************************
 * NAME	: 		void destroy2DArray(a,n0)
 * 
 * DESCRIPTION : 	Template function to destroy a 2D array
 * 
 * INPUTS : 
 * 		T	**a		Pointer to the array
 * 		int	n0		Length of the 1st dimension of the array.
 * 
 * ********************************************************************/
template <class T> void destroy2DArray(T **a, int n0) {
	int i;
	for (i=0;i<n0;i++) {
		delete [] a[i];
	}
	delete[] a;
}

/***********************************************************************
 * NAME	: 		T* appendToArray(a,na,b,nb,n)
 * 
 * DESCRIPTION : 	Template function to append two arrays.
 * 
 * INPUTS : 
 * 		T	*a		Pointer to first array (second will be appended to 
 * 					this).
 * 		int	na		Length of the 1st array.
 * 		T	*b		Pointer to second array
 * 		int	nb		Length of the 2nd array.
 * 
 * OUTPUTS :
 * 		int	n		Total array length.
 * 
 * RETURNS : 
 * 		T	*a		Pointer to the new array
 * 
 * ********************************************************************/
template <class T> T* appendToArray(T *a, int na, T *b, int nb, int *n) {
	n[0] = na + nb; //size of new array
	printf("%d + %d -> %d\n",na,nb,n[0]);
	int *tmp = new T[n[0]]; //temporary array
	if (na > 0) {
		memcpy(tmp,a,na*sizeof(T)); //copy contents of a to tmp
		delete[] a; // delete original a
	}
	memcpy(&tmp[na],b,nb*sizeof(T)); //copy contents of b to tmp
	a = tmp; //transfer pointer to new array
	// must return pointer
	return a;
}

/***********************************************************************
 * NAME	: 		T* arrayCopy(in,out,n)
 * 
 * DESCRIPTION : 	Template function to copy one array to another.
 * 
 * INPUTS : 
 * 		T	*in		Pointer to input array
 * 		T	*out	Pointer to output array
 * 		int	n		Length of arrays
 * 
 * 
 * ********************************************************************/
template <typename T> void arrayCopy(T *in, T *out, int n) {
	int i;
	for (i=0;i<n;i++) {
		out[i] = in[i];
	}
}

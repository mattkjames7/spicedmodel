import numpy as np
from ._CFunctions import _CgetAvMavPS,_CgetAvMavPSCart,_CgetScaledMavPS,_CgetScaledMavPSCart
from ._CTConv import _CTConv

def MavPS(x,y,SMR=None,Coord='xy',ShowDC=True,OnlyDC=False,Validate=True,m=[1,3],RevTrans=True):
	'''
	Get the cold plasmasphere average ion mass model output for a given 
	set of input coordinates.  
	
	Inputs
	======
	x : float
		Array or scalar coordinate (see Coord for more info).
	y : float
		Array or scalar coordinate (see Coord for more info).
	SMR : float | None
		Set to None for the average model, or a float (scalar or array 
		with the same shape as x and y) for the model which is scaled by
		the SMR index.
	Coord : str
		'xy'|'ml' - Denotes the input coordinates provided by the inputs
		x and y, where Coord='xy' corresponds to the x and y SM 
		coordinates and Coord='ml' means that x and y represent MLT (in
		hours) and L-shell (in R_e), respectively.
	ShowDC : bool
		If True (default) then the DC component is included in the model 
		output, otherwise the output just contains the periodic 
		components of the model.
	OnlyDC : bool
		If True (default = False) then the periodic components are 
		ignored and only the DC component is returned.
	Validate : bool
		If True (default) then the positions are checked for validity 
		(2 <= L <= 5.9), where invalid ones are set to NaN.
	m : int
		This should be a 2-element list/tuple/array which contains the
		lowest and highest m-numbers to include in the output (default =
		[1,3]).
	RevTrans : bool
		If True (default) this will reverse the Box-Cox transform of the 
		electron densities back to physical units.
				
	Returns
	=======
	out : float
		Array of average ion mass (amu).
	
	'''
	
	
	#get the number of elements first
	_n = np.int32(np.size(x))
	
	#work out the shape of the input data
	sh = np.shape(x)
	
	#select the possible models based on the input coords
	if Coord == 'ml':
		#MLT and L shell
		av = _CgetAvMavPS
		ann = _CgetScaledMavPS
	else:
		#x and y SM
		av = _CgetAvMavPSCart
		ann = _CgetScaledMavPSCart
	
	#now format the positions correctly
	_x = _CTConv(x,'c_float_ptr')
	_y = _CTConv(y,'c_float_ptr')
	_ShowDC = _CTConv(ShowDC,'c_bool')
	_OnlyDC = _CTConv(OnlyDC,'c_bool')
	_Validate = _CTConv(Validate,'c_bool')
	_m0 = _CTConv(m[0],'c_int')
	_m1 = _CTConv(m[1],'c_int')
	_RevTrans = _CTConv(RevTrans,'c_bool')
	
	#create the output array
	_out = np.zeros(_n,dtype='float32')

	#select and run the model based on whether we have the scaling parameter
	if SMR is None:
		#average model
		av(_n,_x,_y,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_RevTrans,_out)
	else:
		#work out the scaling parameter
		if np.size(SMR) == 1:
			_smr = np.zeros(_n,dtype='float32') + SMR
		else:
			_smr = _CTConv(SMR,'c_float_ptr')
		ann(_n,_x,_y,_smr,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_RevTrans,_out)
		
	#return to original shape
	out = _out.reshape(sh)
	
	return out
		

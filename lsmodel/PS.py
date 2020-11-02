import numpy as np
from ._CFunctions import _CgetAvPS,_CgetAvPSCart,_CgetScaledPS,_CgetScaledPSCart
from ._CTConv import _CTConv

def PS(x,y,SMR=None,Coord='xy',ShowDC=True,OnlyDC=False,Validate=True,m=[1,3],RevTrans=True):
	'''
	Get the plasmaspheric electron density model output 
	for a given set of input coordinates.
	
	'''
	
	#get the number of elements first
	_n = np.int32(np.size(x))
	
	#work out the shape of the input data
	sh = np.shape(x)
	
	#select the possible models based on the input coords
	if Coord == 'ml':
		#MLT and L shell
		av = _CgetAvPS
		ann = _CgetScaledPS
	else:
		#x and y SM
		av = _CgetAvPSCart
		ann = _CgetScaledPSCart
	
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
		

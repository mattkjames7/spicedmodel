import numpy as np
from ._CFunctions import _CgetAvMav,_CgetAvMavCart,_CgetScaledMav,_CgetScaledMavCart
from ._CTConv import _CTConv

def Mav(x,y,F107=None,Coord='xy',ShowDC=True,OnlyDC=False,Validate=True,m=[1,3]):
	'''
	Get the average ion mass model output for a given set of input 
	coordinates.
	
	'''
	
	#get the number of elements first
	_n = np.int32(np.size(x))
	
	#work out the shape of the input data
	sh = np.shape(x)
	
	#select the possible models based on the input coords
	if Coord == 'ml':
		#MLT and L shell
		av = _CgetAvMav
		ann = _CgetScaledMav
	else:
		#x and y SM
		av = _CgetAvMavCart
		ann = _CgetScaledMavCart
	
	#now format the positions correctly
	_x = _CTConv(x,'c_float_ptr')
	_y = _CTConv(y,'c_float_ptr')
	_ShowDC = _CTConv(ShowDC,'c_bool')
	_OnlyDC = _CTConv(OnlyDC,'c_bool')
	_Validate = _CTConv(Validate,'c_bool')
	_m0 = _CTConv(m[0],'c_int')
	_m1 = _CTConv(m[1],'c_int')
	
	#create the output array
	_out = np.zeros(_n,dtype='float32')

	#select and run the model based on whether we have the scaling parameter
	if F107 is None:
		#average model
		av(_n,_x,_y,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_out)
	else:
		#work out the scaling parameter
		if np.size(F107) == 1:
			_f107 = np.zeros(_n,dtype='float32') + F107
		else:
			_f107 = _CTConv(F107,'c_float_ptr')
		ann(_n,_x,_y,_f107,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_out)
		
	#return to original shape
	out = _out.reshape(sh)
	
	return out
		

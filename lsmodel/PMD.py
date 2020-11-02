import numpy as np
from ._CFunctions import _CgetAvPMD,_CgetAvPMDCart,_CgetScaledPMD,_CgetScaledPMDCart
from ._CTConv import _CTConv

def PMD(x,y,F107=None,SMR=None,Coord='xy',ShowDC=True,OnlyDC=False,Validate=True,m=[1,3]):
	'''
	Get the combined plasmasphere/plasmatrough plasma mass density model 
	output for a given set of input coordinates.
	
	'''
	
	#get the number of elements first
	_n = np.int32(np.size(x))

	#work out the shape of the input data
	sh = np.shape(x)
	
	#select the possible models based on the input coords
	if Coord == 'ml':
		#MLT and L shell
		av = _CgetAvPMD
		ann = _CgetScaledPMD
	else:
		#x and y SM
		av = _CgetAvPMDCart
		ann = _CgetScaledPMDCart

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
	
	#check the scaling parameters
	if F107 is None and SMR is None:
		scaled = False
	else:
		#if only one is provided, set the other to a normal-ish value
		if F107 is None:
			F107 = 100.0
		if SMR is None:
			SMR = 0.0

	#select and run the model based on whether we have the scaling parameter
	if SMR is None:
		#average model
		av(_n,_x,_y,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_out)
	else:
		#work out the scaling parameters
		if np.size(SMR) == 1:
			_smr = np.zeros(_n,dtype='float32') + SMR
		else:
			_smr = _CTConv(SMR,'c_float_ptr')
		if np.size(F107) == 1:
			_f107 = np.zeros(_n,dtype='float32') + F107
		else:
			_f107 = _CTConv(F107,'c_float_ptr')
		ann(_n,_x,_y,_f107,_smr,_ShowDC,_OnlyDC,_Validate,_m0,_m1,_out)
		
	#return to original shape
	out = _out.reshape(sh)
	
	return out
		

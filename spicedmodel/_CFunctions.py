import numpy as np
import ctypes as ct
import os
import platform

OS = platform.system()
if OS == 'Linux':
	try:
		liblsmodel = ct.CDLL(os.path.dirname(__file__)+"/__data/spiced/lib/libspiced.so")
	except:
		print('importing liblsmodel.so failed, attempting to recompile')
		path = os.path.dirname(__file__)
		if '/usr/local/' in path:
			sudo = 'sudo '
		else:
			sudo = ''

		CWD = os.getcwd()
		os.chdir(os.path.dirname(__file__)+"/__data/spiced/")
		os.system(sudo+'make clean')
		os.system(sudo+'make')
		os.chdir(CWD)	
		liblsmodel = ct.CDLL(os.path.dirname(__file__)+"/__data/spiced/lib/libspiced.so")
elif OS == 'Windows':
	try:
		liblsmodel = ct.CDLL(os.path.dirname(__file__)+"/__data/spiced/lib/libspiced.dll")
	except:
		print('importing liblsmodel.so failed, attempting to recompile')
		path = os.path.dirname(__file__)

		CWD = os.getcwd()
		os.chdir(os.path.dirname(__file__)+"/__data/spiced/")
		os.system('build.bat')
		os.chdir(CWD)			
		liblsmodel = ct.CDLL(os.path.dirname(__file__)+"/__data/spiced/lib/libspiced.dll")
else:
	print("Looks like you're running this on {:s}, sorry I am unlikely to work...".format(OS))

#define some dtypes
c_char_p = ct.c_char_p
c_bool = ct.c_bool
c_int = ct.c_int
c_float = ct.c_float
c_double = ct.c_double
c_float_ptr = np.ctypeslib.ndpointer(ct.c_float,flags="C_CONTIGUOUS")
c_double_ptr = np.ctypeslib.ndpointer(ct.c_double,flags="C_CONTIGUOUS")
c_int_ptr = np.ctypeslib.ndpointer(ct.c_int,flags="C_CONTIGUOUS")
c_bool_ptr = np.ctypeslib.ndpointer(ct.c_bool,flags="C_CONTIGUOUS")


#Model wrapper functions



#for mav (cold combined)
_CgetAvMav = liblsmodel.getAvMav
_CgetAvMav.restype = None
_CgetAvMav.argtypes = [		c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
						
_CgetAvMavCart = liblsmodel.getAvMavCart
_CgetAvMavCart.restype = None
_CgetAvMavCart.argtypes = [		c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
							
_CgetScaledMav = liblsmodel.getScaledMav
_CgetScaledMav.restype = None
_CgetScaledMav.argtypes = [		c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
						
_CgetScaledMavCart = liblsmodel.getScaledMavCart
_CgetScaledMavCart.restype = None
_CgetScaledMavCart.argtypes = [		c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_float_ptr]	#Output


#for mav (cold PT)
_CgetAvMavPT = liblsmodel.getAvMavPT
_CgetAvMavPT.restype = None
_CgetAvMavPT.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_bool,			#Reverse transform
							c_float_ptr]	#Output
						
_CgetAvMavPTCart = liblsmodel.getAvMavPTCart
_CgetAvMavPTCart.restype = None
_CgetAvMavPTCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
							
_CgetScaledMavPT = liblsmodel.getScaledMavPT
_CgetScaledMavPT.restype = None
_CgetScaledMavPT.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
						
_CgetScaledMavPTCart = liblsmodel.getScaledMavPTCart
_CgetScaledMavPTCart.restype = None
_CgetScaledMavPTCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_bool,			#Reverse transform
									c_float_ptr]	#Output
#for mav (cold PS)
_CgetAvMavPS = liblsmodel.getAvMavPS
_CgetAvMavPS.restype = None
_CgetAvMavPS.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_bool,			#Reverse transform
							c_float_ptr]	#Output
						
_CgetAvMavPSCart = liblsmodel.getAvMavPSCart
_CgetAvMavPSCart.restype = None
_CgetAvMavPSCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
							
_CgetScaledMavPS = liblsmodel.getScaledMavPS
_CgetScaledMavPS.restype = None
_CgetScaledMavPS.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
						
_CgetScaledMavPSCart = liblsmodel.getScaledMavPSCart
_CgetScaledMavPSCart.restype = None
_CgetScaledMavPSCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_bool,			#Reverse transform
									c_float_ptr]	#Output


#for mav (hot)
_CgetAvMavH = liblsmodel.getAvMavH
_CgetAvMavH.restype = None
_CgetAvMavH.argtypes = [c_int,			#number of positions
						c_float_ptr,	#MLT array
						c_float_ptr,	#L-shell
						c_bool,			#ShowDC
						c_bool,			#OnlyDC
						c_bool,			#Validate
						c_int,			#Starting m-number
						c_int,			#Ending m-number
						c_float_ptr]	#Output
						
_CgetAvMavHCart = liblsmodel.getAvMavHCart
_CgetAvMavHCart.restype = None
_CgetAvMavHCart.argtypes = [c_int,			#number of positions
							c_float_ptr,	#x array
							c_float_ptr,	#y array
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
							
_CgetScaledMavH = liblsmodel.getScaledMavH
_CgetScaledMavH.restype = None
_CgetScaledMavH.argtypes = [c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_float_ptr,	#F10.7
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
						
_CgetScaledMavHCart = liblsmodel.getScaledMavHCart
_CgetScaledMavHCart.restype = None
_CgetScaledMavHCart.argtypes = [c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_float_ptr,	#F10.7
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output

#for prob
_CgetAvProb = liblsmodel.getAvProb
_CgetAvProb.restype = None
_CgetAvProb.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
						
_CgetAvProbCart = liblsmodel.getAvProbCart
_CgetAvProbCart.restype = None
_CgetAvProbCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
							
_CgetScaledProb = liblsmodel.getScaledProb
_CgetScaledProb.restype = None
_CgetScaledProb.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
						
_CgetScaledProbCart = liblsmodel.getScaledProbCart
_CgetScaledProbCart.restype = None
_CgetScaledProbCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_float_ptr]	#Output

#for ps
_CgetAvPS = liblsmodel.getAvPS
_CgetAvPS.restype = None
_CgetAvPS.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_bool,			#Reverse transform
							c_float_ptr]	#Output
						
_CgetAvPSCart = liblsmodel.getAvPSCart
_CgetAvPSCart.restype = None
_CgetAvPSCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
							
_CgetScaledPS = liblsmodel.getScaledPS
_CgetScaledPS.restype = None
_CgetScaledPS.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
						
_CgetScaledPSCart = liblsmodel.getScaledPSCart
_CgetScaledPSCart.restype = None
_CgetScaledPSCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_bool,			#Reverse transform
									c_float_ptr]	#Output

#for pt
_CgetAvPT = liblsmodel.getAvPT
_CgetAvPT.restype = None
_CgetAvPT.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
								c_bool,			#Reverse transform
							c_float_ptr]	#Output
						
_CgetAvPTCart = liblsmodel.getAvPTCart
_CgetAvPTCart.restype = None
_CgetAvPTCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
							
_CgetScaledPT = liblsmodel.getScaledPT
_CgetScaledPT.restype = None
_CgetScaledPT.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_bool,			#Reverse transform
								c_float_ptr]	#Output
						
_CgetScaledPTCart = liblsmodel.getScaledPTCart
_CgetScaledPTCart.restype = None
_CgetScaledPTCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_bool,			#Reverse transform
									c_float_ptr]	#Output

#for combined density
_CgetAvDen = liblsmodel.getAvDen
_CgetAvDen.restype = None
_CgetAvDen.argtypes = [	c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
						
_CgetAvDenCart = liblsmodel.getAvDenCart
_CgetAvDenCart.restype = None
_CgetAvDenCart.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
							
_CgetScaledDen = liblsmodel.getScaledDen
_CgetScaledDen.restype = None
_CgetScaledDen.argtypes = [	c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
						
_CgetScaledDenCart = liblsmodel.getScaledDenCart
_CgetScaledDenCart.restype = None
_CgetScaledDenCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_float_ptr]	#Output

#for combined plasma mass density
_CgetAvPMD = liblsmodel.getAvPMD
_CgetAvPMD.restype = None
_CgetAvPMD.argtypes = [		c_int,			#number of positions
							c_float_ptr,	#MLT array
							c_float_ptr,	#L-shell
							c_bool,			#ShowDC
							c_bool,			#OnlyDC
							c_bool,			#Validate
							c_int,			#Starting m-number
							c_int,			#Ending m-number
							c_float_ptr]	#Output
						
_CgetAvPMDCart = liblsmodel.getAvPMDCart
_CgetAvPMDCart.restype = None
_CgetAvPMDCart.argtypes = [		c_int,			#number of positions
								c_float_ptr,	#x array
								c_float_ptr,	#y array
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
							
_CgetScaledPMD = liblsmodel.getScaledPMD
_CgetScaledPMD.restype = None
_CgetScaledPMD.argtypes = [		c_int,			#number of positions
								c_float_ptr,	#MLT array
								c_float_ptr,	#L-shell
								c_float_ptr,	#SMR
								c_bool,			#ShowDC
								c_bool,			#OnlyDC
								c_bool,			#Validate
								c_int,			#Starting m-number
								c_int,			#Ending m-number
								c_float_ptr]	#Output
						
_CgetScaledPMDCart = liblsmodel.getScaledPMDCart
_CgetScaledPMDCart.restype = None
_CgetScaledPMDCart.argtypes = [	c_int,			#number of positions
									c_float_ptr,	#x array
									c_float_ptr,	#y array
									c_float_ptr,	#SMR
									c_bool,			#ShowDC
									c_bool,			#OnlyDC
									c_bool,			#Validate
									c_int,			#Starting m-number
									c_int,			#Ending m-number
									c_float_ptr]	#Output


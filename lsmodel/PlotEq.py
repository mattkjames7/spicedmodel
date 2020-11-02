import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
from mpl_toolkits.axes_grid1 import make_axes_locatable
from .Mav import Mav
from .Prob import Prob
from .PS import PS
from .PT import PT
from .Density import Density
from .PMD import PMD

#default plotting parameters for each plot type (function,colormap,scale,zlog,zlabel)
defargs = { 'prob' 		: (Prob,'seismic',[0.0,1.0],False,'$P(PS)$'),
			'ps'		: (PS,'gnuplot',[100.0,2000.0],True,'$n_{e,ps}$ (cm$^{-3}$)'),
			'pt'		: (PT,'gnuplot',[10.0,200.0],True,'$n_{e,pt}$ (cm$^{-3}$)'),
			'mav'		: (Mav,'gnuplot',[1.0,16.0],False,'$m_{av}$ (amu)'),
			'density'	: (Density,'gnuplot',[10.0,2000.0],True,'$n_e$ (cm$^{-3}$)'),
			'pmd'		: (PMD,'gnuplot',[10.0,30000.0],True,'$\\rho$ (amu cm$^{-3}$)'),}
			
def PlotEq(ptype,F107=None,SMR=None,ShowDC=True,OnlyDC=False,Validate=True,
			m=[1,3],fig=None,maps=[1,1,0,0],rowspan=1,colspan=1,zlog=None,
			scale=None,cmap=None,ColorBar=True,):
	'''
	Plot one of the models in the equatorial plane
	
	'''
	
	#get the default args
	Model,dcmap,dscale,dzlog,zlabel = defargs[ptype]
	

	#create a grid
	nx = 120
	ny = 120
	xrnge = [-6.0,6.0]
	yrnge = [-6.0,6.0]
	xe = np.linspace(xrnge[0],xrnge[1],nx+1)
	ye = np.linspace(yrnge[0],yrnge[1],ny+1)
	
	xc = 0.5*(xe[1:] + xe[:-1])
	yc = 0.5*(ye[1:] + ye[:-1])

	xm,ym = np.meshgrid(xc,yc)
	xem,yem = np.meshgrid(xe,ye)

	

	#calculate the model
	if ptype in ['ps','pt','density','prob']:
		grid = Model(xm,ym,SMR=SMR,ShowDC=ShowDC,OnlyDC=OnlyDC,Validate=Validate,m=m)
	elif ptype == 'mav':
		grid = Model(xm,ym,F107=F107,ShowDC=ShowDC,OnlyDC=OnlyDC,Validate=Validate,m=m)
	else:
		grid = Model(xm,ym,F107=F107,SMR=SMR,ShowDC=ShowDC,OnlyDC=OnlyDC,Validate=Validate,m=m)
	
	#get the scale
	if scale is None:
		scale = dscale
		
	#set norm
	if zlog is None:
		zlog = dzlog
	if zlog:
		norm = colors.LogNorm(vmin=scale[0],vmax=scale[1])
	else:
		norm = colors.Normalize(vmin=scale[0],vmax=scale[1])	

	#set the color map
	if cmap is None:
		cmap = dcmap
		
	
	if fig is None:
		fig = plt
		fig.figure()
	if hasattr(fig,'Axes'):	
		ax = fig.subplot2grid((maps[1],maps[0]),(maps[3],maps[2]),rowspan=rowspan,colspan=colspan)
	else:
		ax = fig
		
	sm = ax.pcolormesh(xem,yem,grid.T,cmap=cmap,norm=norm)

	#set the axis limits
	ax.set_ylim(xrnge)
	ax.set_xlim(yrnge[::-1])
	ax.set_aspect(1.0)

	#set axis titles
	ax.set_ylabel('$x_{SM}$ ($R_E$)')
	ax.set_xlabel('$y_{SM}$ ($R_E$)')	

	if ColorBar:
		divider = make_axes_locatable(ax)
		cax = divider.append_axes("right", size="5%", pad=0.05)

		cbar = plt.colorbar(sm,cax=cax) 
		cbar.set_label(zlabel)
	
	return ax

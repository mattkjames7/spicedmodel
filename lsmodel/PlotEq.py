import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
from mpl_toolkits.axes_grid1 import make_axes_locatable
from .Mav import Mav
from .MavHot import MavHot
from .MavPS import MavPS
from .MavPT import MavPT
from .Prob import Prob
from .PS import PS
from .PT import PT
from .Density import Density
from .PMD import PMD
from .PlotPlanet import PlotPlanet

#default plotting parameters for each plot type (function,colormap,scale,zlog,zlabel)
defargs = { 'prob' 		: (Prob,'seismic',[0.0,1.0],False,'$P(PS)$'),
			'ps'		: (PS,'gnuplot',[100.0,2000.0],True,'$n_{e,ps}$ (cm$^{-3}$)'),
			'pt'		: (PT,'gnuplot',[10.0,200.0],True,'$n_{e,pt}$ (cm$^{-3}$)'),
			'mav'		: (Mav,'gnuplot',[1.0,6.0],False,'$m_{av}$ (amu)'),
			'mavhot'	: (MavHot,'gnuplot',[1.0,16.0],False,'Hot $m_{av}$ (amu)'),
			'mavps'		: (MavPS,'gnuplot',[1.0,6.0],False,'$m_{av}$ (amu)'),
			'mavpt'		: (MavPT,'gnuplot',[1.0,6.0],False,'$m_{av}$ (amu)'),
			'density'	: (Density,'gnuplot',[10.0,2000.0],True,'$n_e$ (cm$^{-3}$)'),
			'pmd'		: (PMD,'gnuplot',[10.0,5000.0],True,'$\\rho$ (amu cm$^{-3}$)'),}
			
def PlotEq(ptype,SMR=None,F107=None,ShowDC=True,OnlyDC=False,Validate=True,
			m=[1,3],fig=None,maps=[1,1,0,0],rowspan=1,colspan=1,zlog=None,
			scale=None,cmap=None,ColorBar=True,NoonTop=True,xrnge=[-6.0,6.0],
			yrnge=[-6.0,6.0],dx=0.1,dy=0.1):
	'''
	Plot one of the models in the equatorial plane
	
	======
	ptype : str
		This will determine which model to plot: 'prob'|'ps'|'pt'|'mav'|
		'density'|'pmd'. 
	SMR : float | None
		Set to None for the average model, or a float (scalar or array 
		with the same shape as x and y) for the model which is scaled by
		the SMR index.
	F107 : float | None
		Set to None for the average model, or a float (scalar or array 
		with the same shape as x and y) for the model which is scaled by
		the f10.7 index.
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
	fig : None | object
		If fig=None - a new plot window is created.
		If fig=matplotlib.pyplot - the current plot window is used, new
		subplot is created.
		If fig=matplotlib.pyplot.Axes instance - the current set of axes
		is used.
	maps : array-like
		This should be a 4-element list/tuple/array of integers where 
		maps=[xmaps,ymaps,xmap,ymap] and:
		xmaps : number of subplots in the horizontal direction
		ymaps : number of subplots in the vertical direction
		xmap : position of the current plot horizontally, starting
			at 0 (from the left)
		ymap : position of the current plot vertically, starting at 0
			(from the top)
	rowspan : number of rows of subplots to occupy with this plot.
	colspan : number of columns of subplots to occupy with this plot.
	zlog : None | bool
		Sets the color bar to a log-scale if True. If None, the default 
		for the plot type is used.
	scale : None | array-like
		If set to a 2-element array, this sets the limits of the color 
		scale. If set to None then the default is used.
	cmap : None | str
		Set to the name of a matplotlib color scale.
	ColorBar : bool
		If True, then display a color bar next to the subplot.
		
	Returns
	=======
	ax : matplotlib.pyplot.Axes
		The instance of the current set of plot axes.
	'''
	
	#get the default args
	Model,dcmap,dscale,dzlog,zlabel = defargs[ptype]
	

	#create a grid
	nx = np.int32(np.round((xrnge[1]-xrnge[0])/dx))
	ny = np.int32(np.round((yrnge[1]-yrnge[0])/dy))
	xe = np.linspace(xrnge[0],xrnge[1],nx+1)
	ye = np.linspace(yrnge[0],yrnge[1],ny+1)
	
	xc = 0.5*(xe[1:] + xe[:-1])
	yc = 0.5*(ye[1:] + ye[:-1])

	xm,ym = np.meshgrid(xc,yc)
	xem,yem = np.meshgrid(xe,ye)

	

	#calculate the model
	if ptype == 'mavhot':
		grid = Model(xm,ym,F107=F107,ShowDC=ShowDC,OnlyDC=OnlyDC,Validate=Validate,m=m)
	else:
		grid = Model(xm,ym,SMR=SMR,ShowDC=ShowDC,OnlyDC=OnlyDC,Validate=Validate,m=m)
	
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
		
	if NoonTop:
		sm = ax.pcolormesh(xem,yem,grid.T,cmap=cmap,norm=norm)
	else:
		sm = ax.pcolormesh(yem.T,xem.T,grid,cmap=cmap,norm=norm)

	ax.set_aspect(1.0)

	if NoonTop:
		#set the axis limits
		ax.set_ylim(xrnge)
		ax.set_xlim(yrnge[::-1])

		#set axis titles
		ax.set_ylabel('$x_{SM}$ ($R_E$)')
		ax.set_xlabel('$y_{SM}$ ($R_E$)')	
	else:
		#set the axis limits
		ax.set_xlim(xrnge)
		ax.set_ylim(yrnge)

		#set axis titles
		ax.set_xlabel('$x_{SM}$ ($R_E$)')
		ax.set_ylabel('$y_{SM}$ ($R_E$)')	
	
	#add in the Earth
	PlotPlanet(ax,NoonTop=NoonTop)

	if ColorBar:
		divider = make_axes_locatable(ax)
		cax = divider.append_axes("right", size="5%", pad=0.05)

		cbar = plt.colorbar(sm,cax=cax) 
		cbar.set_label(zlabel)
		
	#add title
	title = []
	if not SMR is None:
		title.append('SMR={:5.1f} nT'.format(SMR))
	if not F107 is None:
		title.append('F10.7={:5.1f} sfu'.format(F107))
	
	if len(title) > 0:
		title = '  '.join(title)
		ax.set_title(title)
	
	return ax

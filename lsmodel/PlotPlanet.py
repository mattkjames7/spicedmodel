import numpy as np

def PlotPlanet(ax,R=1.0,Center=[0.0,0.0,0.0],zorder=10,NoonTop=True):
	'''
	Plot the planet in the centre of a set of Axes.
	
	Inputs
	======
	ax : matplotlib.pyplot.Axes instance
		This is the set of axes to plot on.
	R : float
		Radius to plot planet with.
	Center : float
		3-element array-like object containing the x, y and z 
		coordinates in the plot at which to center the planet.
	zorder : float
		This controls whether the planet appears above or below other 
		elements of the plot.
	
	'''
	
	a = 2*np.pi*np.arange(361,dtype='float32')/360
	x = R*np.sin(a) + Center[0]
	y = R*np.cos(a) + Center[1]
	
	if NoonTop:
		ax.fill(y,x,color=[1.0,1.0,1.0],zorder=zorder)
		ax.plot(y,x,color=[0,0,0],zorder=zorder+1)
		ax.fill(y[180:360],x[180:360],color=[0.0,0.0,0.0],zorder=zorder+1)
	else:
		ax.fill(x,y,color=[1.0,1.0,1.0],zorder=zorder)
		ax.plot(x,y,color=[0,0,0],zorder=zorder+1)
		ax.fill(x[180:360],y[180:360],color=[0.0,0.0,0.0],zorder=zorder+1)


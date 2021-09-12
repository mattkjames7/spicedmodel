# spicedmodel

Python wrapper for the Scalable Plasma Ion Composition and Electron Density (SPICED) model.

The paper:

James, M. K., Yeoman, T.K., Jones, P., Sandhu, J. K., Goldstein, J. (2021), The Scalable Plasma Ion Composition and Electron Density (SPICED) model for Earth's inner magnetosphere, *J. Geophys. Res. Space Physics*,  https://doi.org/10.1029/2021JA029565

[![DOI](https://zenodo.org/badge/244674501.svg)](https://zenodo.org/badge/latestdoi/244674501)

## Installation

### Using `pip`

This will download the package from PyPI:

```bash
pip3 install spicedmodel --user
```

### From Source

Obtain the latest release from https://github.com/mattkjames7/spicedmodel

```bash
git clone https://github.com/mattkjames7/spicedmodel
cd spicedmodel
```

Either install using `setup.py`:

```bash
python3 setup.py install --user
```

or by building a wheel:

```bash
python3 setup.py bdist_wheel
pip3 install dist/spicedmodel-XXX.whl --user
```

where `"XXX"` is the rest of the file name, which will vary depending upon the current version.

## Usage

Load `python3` or `ipython3`, and import

```python
import spicedmodel
```

### Accessing the models

There are four models, plus two additional combinations of these models:

* Plasmasphere average ion mass, *m<sub>av,ps</sub>*: `spicedmodel.MavPS`
* Plasmatrough average ion mass, *m<sub>av,pt</sub>*: `spicedmodel.MavPT
* Combined average ion mass, *m<sub>av</sub>*: `spicedmodel.Mav`
* Hot average ion mass, *m<sub>av</sub>*: `spicedmodel.MavHot`
* Probability of being within the plasmasphere, *P*: `spicedmodel.Prob`
* Plasmasphere electron density, *n<sub>e,ps</sub>*: `spicedmodel.PS`
* Plasmatrough electron density, *n<sub>e,pt</sub>*: `spicedmodel.PT`
* Combined electron density, *n<sub>e</sub>* (a combination of plasmasphere, plasmatrough and probability models): `spicedmodel.Density`
* Combined plasma mass density, &rho;: `spicedmodel.PMD`  

The average versions of each model can be accessed simply by providing the positions in the equatorial plane where you would like them, e.g.:

```python
#either using SM x and y coordinates
P = spicedmodel.Prob(x,y)

#or using MLT (M) and L-Shell (L)
P = spicedmodel.Prob(M,L,Coord='ml')
```

The scaled models can be accessed using the same functions, this time including the `SMR` keyword (for `Mav`, `MavPS`, `MavPT`, `Prob`, `PS`, `PT`, `Density` or `PMD`) or `F107` (for `MavHot`), e.g.:

```python
#electron density
ne = spicedmodel.Density(x,y,SMR=-75.0)

#average ion mass
mav = spicedmodel.Mav(x,y,SMR=-75.0)

#plasma mass density, effectively ne*mav
pmd = spicedmodel.PMD(x,y,SMR=-75.0)
```

### Plotting the models

A simple function is included, `PlotEq`, which allows the plotting of any of the models in the equatorial plane. e.g.:

```python
ax = spicedmodel.PlotEq(ptype,SMR=-75.0)
```

where `ptype` is used to tell the function which model to plot, available options are: `'mav'|'mavps'|'mavpt'|'mavhot'|'prob'|'ps'|'pt'|'density'|'pmd'`.

The following code produces a plot with all 6 models when SMR = -75 nT

```python
import matplotlib.pyplot as plt
import spicedmodel

#create the plot window
plt.figure(figsize=(8,7))

#set the parameters of the models
smr = -70.0

#plot the average ion mass
ax0 = spicedmodel.PlotEq('mav',SMR=smr,fig=plt,maps=[2,2,0,0])

#plot probability 
ax1 = spicedmodel.PlotEq('prob',SMR=smr,fig=plt,maps=[2,2,1,0])

#plot electron density 
ax4 = spicedmodel.PlotEq('density',SMR=smr,fig=plt,maps=[2,2,0,1])

#plot plasma mass density
ax5 = spicedmodel.PlotEq('pmd',SMR=smr,fig=plt,maps=[2,2,1,1])

#adjust everything to fit
plt.tight_layout()
```

![example.png](example.png)

For more information and options, see the `docstring`: `spicedmodel.PlotEq?`






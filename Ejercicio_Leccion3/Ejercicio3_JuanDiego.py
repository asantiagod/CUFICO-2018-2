#Ejercicio Numero 3- Juan Diego Mazo Vásquez

import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from numpy import  linspace, sin, polyfit, polyval, exp, load
from scipy.interpolate import lagrange

x=load("x_spectra.npy")
y=load("y_spectra.npy")

def fit(x, a,b,c,d,e,f,g,h):
	return a* exp(-(x-b)**2 /c) + d*exp(-(x-e)**2 /f) +g*x + h

init_vals = [120,10,2,130,30,3, 0.02, 100 ]
best_vals, covar = curve_fit(fit, x, y, p0=init_vals)
print (best_vals)


plt.scatter(x,y)
plt.plot(linspace(0,100,500),fit(linspace(0,100,500),*best_vals),"r-")
plt.show()


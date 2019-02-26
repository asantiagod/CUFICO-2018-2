#

from numpy import sqrt, pi, exp, linspace, random, load, sort
from scipy.optimize import curve_fit
import matplotlib.pylab as plt


x=load("x_spectra.npy")  # Se cargan los datos
y=load("y_spectra.npy")

plt.plot(x, y)
#plt.show()

def gaussian(x, amp1, cen1, wid1, amp2, cen2, wid2, a, b):
        """Esta funcion grafica dos gaussianas y una recta"""
	return amp1*exp(-(x-cen1)**2 /wid1) + amp2*exp(-(x-cen2)**2 /wid2) + a*x + b

init_vals =[121, 10, 1, 130, 30.3, 1, 1, 0]  #Se proponen los valores iniciales
best_vals, covar = curve_fit(gaussian, x, y, p0=init_vals) #Se encuentran los valores que mas se ajustan
plt.plot(linspace(0,100,100),gaussian(linspace(0,100,100),best_vals[0],best_vals[1],best_vals[2], best_vals[3], best_vals[4], best_vals[5], best_vals[6], best_vals[7]),"r-")  #Se plotea la grafica y el ajuste
plt.title("Espectro")
plt.show()



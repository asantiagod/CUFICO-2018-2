from numpy import *
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

x= load("x_spectra.npy")
y= load("y_spectra.npy")

def tramos(x, amp1, cen1, wid1, amp2, cen2, wid2, a, b):
	return amp1 * exp(-(x-cen1)**2 /wid1) + amp2 * exp(-(x-cen2)**2 /wid2) + a*x+b
	
init_vals= [1, 10, 1, 1, 30, 1, -0.03, 100]
best_vals, covar= curve_fit(tramos, x, y, p0= init_vals)
plt.plot(linspace(0,100,100), tramos(linspace(0,100,100), best_vals[0], best_vals[1], best_vals[2], best_vals[3], best_vals[4], best_vals[5], best_vals[6], best_vals[7]), "r-")		
plt.scatter(x, y)
plt.show()

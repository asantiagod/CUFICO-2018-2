from numpy import sqrt, pi, exp, linspace, load

def gaussian(x, amp1, cen1, wid1, amp2, cen2, wid2, a, b):
	return (amp1 * exp(-(x-cen1)**2 /wid1)) + (amp2 * exp(-(x-cen2)**2 /wid2)) + a*x + b

x=load("x_spectra.npy")
y=load("y_spectra.npy")

from scipy.optimize import curve_fit

init_vals = [120,10,10,130,30,10,0,100]	# for [amp, cen, wid]
best_vals, covar = curve_fit(gaussian, x, y, p0=init_vals)
print best_vals

import matplotlib.pyplot as plt

plt.scatter(x, y)
plt.plot(linspace(0,100,1000),gaussian(linspace(0,100,1000),best_vals[0],best_vals[1],best_vals[2],best_vals[3],best_vals[4],best_vals[5],best_vals[6],best_vals[7]),"r-")
plt.show()

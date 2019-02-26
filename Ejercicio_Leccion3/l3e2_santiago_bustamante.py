#!/usr/bin/env pyhon
"""Ejercicio 2 Leccion 3

  ~Santiago Bustamante
  FI: 21 de Agosto 2018
  UM: 21 de Agosto 2018
"""

from numpy import load, exp, arange
import matplotlib.pyplot as plt

def gaussian2(x, amp1, cen1, wid1, amp2, cen2, wid2, b, a):
    return amp1*exp(-(x-cen1)**2/wid1) + amp2*exp(-(x-cen2)**2/wid2) + b + a*x

x = load("x_spectra.npy")
y = load("y_spectra.npy")
xc = arange(min(x), max(x), 1e-2)

from scipy.optimize import curve_fit
init_vals = [120,10,10,130,30,10, 100, 10]    #for [amp1,amp2,cen1,cen2,wid1,wid2]
best_vals, covar = curve_fit(gaussian2, x, y, p0=init_vals)
print best_vals

plt.figure()
plt.scatter(x,y)
plt.plot(xc, gaussian2(xc,best_vals[0], best_vals[1], best_vals[2],best_vals[3], best_vals[4], best_vals[5], best_vals[6], best_vals[7]), color='r')
plt.show()

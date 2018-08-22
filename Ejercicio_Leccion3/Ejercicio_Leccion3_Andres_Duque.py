from numpy import sqrt, pi, exp, linspace, load

def gaussian(x, amp, cen, wid):
    return amp * exp(-(x-cen)**2 /wid)

def lin(x,a,b):
    return a*x +b

def func(x,a,b, #linea recta
         a1,u1,sig1, #gaussiana
         a2,u2,sig2): #gaussiana
    return lin(x,a,b) + gaussian(x,a1,u1,sig1)+ gaussian(x,a2,u2,sig2)
    
x=load("x_spectra.npy")
y=load("y_spectra.npy")

from scipy.optimize import curve_fit
init_vals = [0.05, 100,  # linea recta
             120, 10, 5, # Primer gaussiana
             130, 30, 5] # Segunda gaussiana
best_vals, covar = curve_fit(func, x, y, p0=init_vals)
print(best_vals)

import matplotlib.pyplot as plt
plt.scatter(x, y)
plt.plot(x,func(x,best_vals[0],best_vals[1],
                best_vals[2],best_vals[3],best_vals[4],
                best_vals[5],best_vals[6],best_vals[7]))
plt.show()
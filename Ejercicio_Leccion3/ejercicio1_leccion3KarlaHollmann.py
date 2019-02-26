from numpy import sqrt, pi, exp, linspace, save, load, random
import matplotlib.pyplot as plt

def fun(x, amp, cen, wid, amp2, cen2, wid2, a, b):
   return (amp * exp(-(x-cen)**2 /wid)) + (amp2 * exp(-(x-cen2)**2 /wid2))+a*x+b

x=load("x_spectra.npy")
y=load("y_spectra.npy")

from scipy.optimize import curve_fit

init_vals = [120,10,10,130,30,10,1,100]     
best_vals, covar = curve_fit(fun, x, y, p0=init_vals)
print(best_vals)


plt.scatter(x, y)
plt.plot(linspace(0,100,100),fun(linspace(0,100,100),best_vals[0],best_vals[1],best_vals[2],best_vals[3],best_vals[4],best_vals[5],best_vals[6],best_vals[7]),"r-")
       
plt.show()

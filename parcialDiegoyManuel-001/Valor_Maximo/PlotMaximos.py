from numpy import sqrt, pi, log, linspace, load
def loga(x, a, b):
         return a*log(x)+b
x=[5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60]
y= [0.025, 0.061, 0.066, 0.088, 0.081, 0.075, 0.161, 0.141, 0.085, 0.204, 0.123, 0.126]
from scipy.optimize import curve_fit
init_vals = [0.049,-0.06]
best_vals, covar = curve_fit(loga, x, y, p0=init_vals)
print (best_vals)
import matplotlib.pyplot as plt
plt.scatter(x, y)
plt.plot(linspace(0,100,100),loga(linspace(0,100,100),best_vals[0],best_vals[1]),"r-")
plt.show()

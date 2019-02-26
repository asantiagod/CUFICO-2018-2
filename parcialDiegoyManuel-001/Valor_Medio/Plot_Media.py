from numpy import sqrt, pi, log,exp, linspace, load
def loga(x, amp, cen,wid):
         return amp * exp(-(x-cen)**2 /wid)
x=[5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60]
y=[0.01126, 0.01922, 0.02913, 0.02776, 0.03363, 0.02425, 0.03974, 0.03996, 0.03813, 0.04933, 0.01953, 0.04089]
from scipy.optimize import curve_fit
init_vals = [0.14,49,1406]
best_vals, covar = curve_fit(loga, x, y, p0=init_vals)
print (best_vals)
import matplotlib.pyplot as plt
plt.scatter(x, y)
plt.plot(linspace(0,100,100),loga(linspace(0,100,100),best_vals[0],best_vals[1],best_vals[2]),"r-")
plt.show()

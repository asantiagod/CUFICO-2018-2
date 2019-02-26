from numpy import sqrt, pi, exp, linspace, load
import matplotlib.pyplot as plt

def gaussian(x, amp1, cen1, wid1, amp2, cen2, wid2, m, b):
    return amp1 * exp(-(x-cen1)**2 /wid1) + amp2 * exp(-(x-cen2)**2 /wid2) + m*x + b
    
x=load("x_spectra.npy")
y=load("y_spectra.npy")


import matplotlib.pyplot as plt
plt.scatter(x, y)
plt.show()


from scipy.optimize import curve_fit
init_vals2 = [1,10,1,1,30,1, 0.3,100]
best_vals, covar = curve_fit(gaussian, x, y , p0 = init_vals2)
print best_vals

plt.scatter(x, y)
plt.plot(linspace(-1,100,1000),gaussian(linspace(-1,100,1000),best_vals[0],best_vals[1],best_vals[2],best_vals[3],best_vals[4],best_vals[5],best_vals[6],best_vals[7]),"r-")
plt.show()

import numpy as np
import  matplotlib.pylab as plt

X=np.load('x_spectra.npy')
Y=np.load('y_spectra.npy')

def gaussian(x, amp1, cen1, wid1, amp2, cen2, wid2,a,b):
    return amp1* np.exp(-(x-cen1)**2 /wid1) + amp2* np.exp(-(x-cen2)**2 /wid2) + a*x + b

from scipy.optimize import curve_fit
init_vals = [120,10,3,128,30,5,0.02,100]
best_vals, covar = curve_fit(gaussian, X, Y, p0=init_vals)


X1 = np.linspace(0,100,1000)
Y1 = gaussian(np.linspace(0,100,1000),best_vals[0],best_vals[1],best_vals[2],best_vals[3],best_vals[4],best_vals[5],best_vals[6],best_vals[7])

plt.figure(figsize=(10,5))
plt.plot (X,Y,'b',label="Datos")
plt.plot(X1,Y1,'g',label="Ajuste")
plt.legend(prop={'size': 15})
plt.grid()
plt.show()

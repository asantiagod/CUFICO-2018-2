from numpy import sqrt,pi,exp,linspace, load, average, std
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

x = load("x_spectra.npy")
y = load("y_spectra.npy")


def two_gaussians_and_line(X, amp1, cen1, wid1, amp2, cen2, wid2,a,b):
	return amp1*exp(-(x-cen1)**2/wid1)+ amp2*exp(-(x-cen2)**2/wid2) + a *x +b


init_vals = [110, 10, 1, 130, 30, 1, -0.02, 90] # muy alta sensibilidad al valor inicial de cen1, cen2


Params, covar = curve_fit(two_gaussians_and_line, x, y, p0=init_vals)
print(Params)

y_fit = two_gaussians_and_line(x, Params[0], Params[1], Params[2], Params[3], Params[4], Params[5], Params[6], Params[7])


plt.plot(x,y,".k")
plt.plot(x,y_fit, "-r")
plt.show()

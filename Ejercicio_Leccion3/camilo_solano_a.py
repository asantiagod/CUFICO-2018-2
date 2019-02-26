from numpy import sqrt, pi, exp, linspace, save,load,random
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def gaussian(x, amp, cen, wid):
	return amp * exp(-(x-cen)**2 /wid)+100

def p1(x,a,b):
	return a+x*b

def gaussian2(x, a1, b1, c1,a2, b2, c2):
	return a1 * exp(-(x-b1)**2 /c1)+a2 * exp(-(x-b2)**2 /c2)




def p3(x,a,b,c,d):
	return a+b*x+c*x*x+d*x*x*x

"""
N=1000
x = linspace(-10,10,N)
y = gaussian(x, 1, 1, 1) + random.normal(0, 0.2, len(x))


save("x_coord_noisy",x)
save("y_coord_noisy",y)
import matplotlib.pyplot as plt
plt.scatter(x, y)"""




x=load("x_spectra.npy")
y=load("y_spectra.npy")
plt.scatter(x, y)
print(len(x))


cut=200
init_vals = [120, 10, 5] 
best_vals, covar = curve_fit(gaussian, x[:cut], y[:cut], p0=init_vals)
print (best_vals)
plt.plot(x[:cut],gaussian(x[:cut],best_vals[0],best_vals[1],best_vals[2]),"r-")

L=cut+200
init_vals = [130,30,10] 
best_vals, covar = curve_fit(gaussian, x[cut:], y[cut:], p0=init_vals)
print (best_vals)
plt.plot(x[cut:L],gaussian(x[cut:L],best_vals[0],best_vals[1],best_vals[2]),"r-")

init_vals = [100,-1] 

best_vals, covar = curve_fit(p1, x[cut+L:], y[cut+L:], p0=init_vals)
print (best_vals)
plt.plot(x[L:],p1(x[L:],best_vals[0],best_vals[1]),"r-")

plt.show()
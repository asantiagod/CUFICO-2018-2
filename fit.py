import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def func(x, a, b, c):
    return a * np.exp(b*0.01* x) + c

x = np.linspace(5,60,55)
y = [4.75840e-05, 5.43641e-05, 6.11506e-05, 6.37069e-05, 6.69806e-05, 1.72117e-04, 1.89360e-04, 2.27382e-04, 2.64877e-04, 2.63542e-04, 			2.95507e-04, -1.14680e-04, 5.71753e-04, 5.70742e-04, 9.15939e-04, 1.00213e-03, 1.07957e-03, 1.04668e-03, 1.28848e-03, 			1.33655e-03, 1.32079e-03, 1.35788e-03, 1.31631e-03, 1.12270e-03, 2.71783e-03, 2.63591e-03, 2.73855e-03, 2.61657e-03, 			2.87275e-03, 3.00163e-03, 2.50560e-03, 2.70381e-03, 4.86661e-03, 4.33370e-03, 5.24101e-03, 6.55424e-03, 5.39487e-03, 			6.16986e-03, 6.41996e-03, 7.82181e-03, 4.53910e-03, 1.03016e-02, 1.13209e-02, 1.22221e-02, 1.16162e-02, 1.16933e-02, 			1.41178e-02, 1.64583e-02, -1.96012e-03, 8.86712e-03, 1.35385e-02, 1.27278e-02, 1.35622e-02, 1.46033e-02, 1.54941e-02]

##yn = y + 0.02*np.random.normal(size=len(x))

popt, pcov = curve_fit(func, x, y)
plt.figure()
plt.plot(x, y, 'ko', label="Datos")
plt.plot(x, func(x, *popt), 'r-', label="Aproximacion exponencial de la forma a*exp(b*0.01*x)+c ")
plt.plot(x, func(x, *popt), 'g--', label=popt)# % tuple(popt))
#plt.plot(label=a)
plt.legend()
plt.show()



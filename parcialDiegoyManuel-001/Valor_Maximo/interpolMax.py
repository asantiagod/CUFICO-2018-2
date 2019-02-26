import numpy as np
from scipy.interpolate import interp1d
x=[5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60]
y= [0.025, 0.061, 0.066, 0.088, 0.081, 0.075, 0.161, 0.141, 0.085, 0.204, 0.123, 0.126]
f = interp1d(x, y)
f2 = interp1d(x, y, kind='cubic')
xnew = np.linspace(5, 60, num=100, endpoint=True)
import matplotlib.pyplot as plt
plt.plot(x, y, 'o', xnew, f(xnew), '-', xnew, f2(xnew), '--')
plt.legend(['data', 'linear', 'cubic'], loc='best')
plt.show()

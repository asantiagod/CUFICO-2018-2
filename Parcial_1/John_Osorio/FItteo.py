import numpy as np
from scipy.stats import norm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
Data = np.loadtxt("data.dat")
_mu = []
_max = []
_N = Data[:,0]
for dat in Data:
    (mu, sigma) = norm.fit(dat[1:])
    n, bins, patches = plt.hist(dat[1:], 60, normed=1, facecolor='green', alpha=0.75)
    y = mlab.normpdf( bins, mu, sigma)
    l = plt.plot(bins, y, 'r--', linewidth=2)
    _mu = np.append(_mu, mu)
    _max = np.append(_max, max(dat[1:]))
    plt.xlabel('Smarts')
    plt.ylabel('Probability')
    plt.title(r'$\mathrm{Histogram\ of\ IQ:}\ \mu=%.3f,\ \sigma=%.3f$' %(mu, sigma))
    plt.grid(True)
    plt.show()
print(_N)
print(_mu)
print(_max)
np.savetxt("statistics.dat", np.c_[_N, _mu, _max])
plt.plot(_N, _mu, '.')
p = np.polyfit(_N, _mu, 2, rcond=None, full=False)
x = np.linspace(_N.min(), _N.max(), _N.max())
y = np.ones(len(x))*p[-1]

for i in range(1, len(p)):
    y = y + p[i-1]*x**(len(p)-i)
plt.title("Tiempo estabilizacion central")
plt.plot(x, y)
plt.xlabel("N")
plt.ylabel("Tiempo [ms]")
plt.grid(True)
plt.show()
plt.plot(_N, _max, '.')
p = np.polyfit(_N, _max, 9, rcond=None, full=False)
x = np.linspace(_N.min(), _N.max(), _N.max())
y = np.ones(len(x))*p[-1]

for i in range(1, len(p)):
    y = y + p[i-1]*x**(len(p)-i)
plt.title("Tiempo estabilizacion maximo")
plt.plot(x, y)
plt.xlabel("N")
plt.ylabel("Tiempo [ms]")
plt.grid(True)
plt.show()


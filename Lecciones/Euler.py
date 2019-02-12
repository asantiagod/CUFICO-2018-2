import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

def Euler(xn, yn, h, MyF):
    return yn + (h*MyF(yn,xn))

def EulerM(xn, yn, h, MyF):
    ynm=yn+0.5*h*MyF(xn,yn)
    xnm=xn+0.5*h
    return yn + (h*MyF(ynm,xnm))

def MyFirstODE(y,x):
    return x-y #y'=x-y

def ExactSolution(x):
    return x-1+2*np.exp(-x)


NumPuntos=np.array([10,100,1000,10000])
x0=0.
xf=5.
y0 = 1.0
h=(xf-x0)/NumPuntos

y1_difference = []
yE_difference = []
yEM_difference = []

for j in NumPuntos:
    EulerSolutions=[]
    EulerSolutionsM=[]

    xs = np.linspace(x0,xf,j)
    
    EulerSolutions.append(y0)
    EulerSolutionsM.append(y0)

    for i in xs[1:]:
        CurrentSolution=Euler(i, EulerSolutions[-1], ((xf-x0)/j), MyFirstODE)
        EulerSolutions.append(CurrentSolution)
        CurrentSolutionM=EulerM(i, EulerSolutionsM[-1], ((xf-x0)/j), MyFirstODE)
        EulerSolutionsM.append(CurrentSolutionM)
    
    ys = odeint(MyFirstODE, y0, xs)
    ys = np.array(ys).flatten()

    y_exact=ExactSolution(xs)

    y1_difference.append(np.mean(np.abs(ys - y_exact)))
    yE_difference.append(np.mean(np.abs(y_exact - EulerSolutions)))
    yEM_difference.append(np.mean(np.abs(y_exact - EulerSolutionsM)))


#plt.plot(xs, ys, "r")
#plt.plot(xs, EulerSolutions, "b")
#plt.plot(xs, EulerSolutionsM, "m")
#plt.plot(xs, y_exact, "g--")

#y1_difference = np.abs(ys - y_exact)
#yE_difference = np.abs(y_exact - EulerSolutions)
#yEM_difference = np.abs(y_exact - EulerSolutionsM)

#plt.semilogy(xs, y1_difference,"r")
#plt.semilogy(xs, yE_difference,"b")
#plt.semilogy(xs, yEM_difference,"m")

plt.semilogy(h, y1_difference,"r")
plt.semilogy(h, yE_difference,"b")
plt.semilogy(h, yEM_difference,"m")

plt.show()

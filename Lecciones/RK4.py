import numpy as np
#import matplotlib.pyplot as plt
from scipy.integrate import odeint

def MyFirstODE(y,x):
    return x-y #y'=x-y

def ExactSolution(x):
    return x-1+2*np.exp(-x)

def MyRK4(xn, yn, h, MyF):
    k1=h*MyF(yn,xn)
    k2=h*MyF(yn+(0.5*h*k1),xn+(0.5*h))
    k3=h*MyF(yn+(0.5*h*k2),xn+(0.5*h))
    k4=h*MyF(yn+h*k3,xn+h)
    return yn+((1./6)*(k1+(2*k2)+(2*k3)+k4))

x0=0.
y0 = 1.0
xf=5.

Sampling=10
xs = np.linspace(x0,xf,Sampling)
ys=[]
ys.append(y0)

for i in xs[1:]:
    ys.append(MyRK4(i, ys[-1], ((xf-x0)/Sampling), MyFirstODE))

    
print(xs)
print(ys)

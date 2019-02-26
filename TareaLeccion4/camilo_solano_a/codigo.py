import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class Particle:

    cargada = True
    def __init__(self, x, v, m, q):
        self.x = np.array(x)
        self.v = np.array(v)
        self.m = m
        self.q = q

    def move(self,time_step,B,f1):
            
        
        f2=self.q*np.cross(self.v,B)
        
        
        a=(f1+f2)/self.m
        self.v= self.v + a*time_step
        self.x= self.x + self.v*time_step
        return self.x


N=10000
time_step=0.01
B=[0,0,10]


p1=Particle([0,0,0],[0,1,0],10,1)
p2=Particle([1,0,0],[0,1,0],10,-1)

s1=[]
s2=[]

for n in range(N):
        
        r_vec = np.subtract(np.array(p1.x), np.array(p2.x))
        r=np.linalg.norm(r_vec)
        if r>0.1:
                f1=-(p1.q)*(p2.q)*r_vec/r**3
        else:
                f1=0
                
        s1.append(p1.move(time_step,B,-f1))
        s2.append(p2.move(time_step,B,f1))


plt.plot([s[0] for s in s1], [s[1] for s in s1])
plt.plot([s[0] for s in s2], [s[1] for s in s2])

plt.show()

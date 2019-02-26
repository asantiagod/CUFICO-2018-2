# -*- coding: utf-8 -*-
"""
Created on Fri Aug 31 07:07:51 2018

@author: lv
"""

import matplotlib as plt
from AL4_DiegoH import Particle as Particle

P1=Particle(0.0,0.0,0.0,0.00,0.0,0.0,10.00,1.0)
P2=Particle(1.0,0.0,0.0,0.00,0.0,0.0,10.00,-1.0)

l=0
x=[];y=[];z=[]
vx=[];vy=[]
x2=[];y2=[];z2=[]
vx2=[];vy2=[]
Bz=10.00
K=1 #supongamos la constante electrica igual a 1 para no reducir el tamaño de las cargas y del campo
d=0.0
while l<5000:
    x.append(P1.X); y.append(P1.Y);z.append(P1.Z)
    vx.append(P1.VX);vy.append(P1.VY)
    x2.append(P2.X); y2.append(P2.Y);z2.append(P2.Z)
    vx2.append(P2.VX);vy2.append(P2.VY)
    d=((P2.X-P1.X)**2+(P2.Y-P1.Y)**2)**(1/2)
    if d<=0.01:
        break
    fx=(P2.X-P1.X)/(d**3)+P1.Carga*P1.VY*Bz
    fy=(P2.Y-P1.Y)/(d**3)-1.0*P1.Carga*P1.VX*Bz
    fx2=(P1.X-P2.X)/(d**3)+P2.Carga*P2.VY*Bz
    fy2=(P1.Y-P2.Y)/(d**3)-1.0*P2.Carga*P2.VX*Bz
    
    P1.time_evol(fx,fy,0.0,0.001)
    P1.time_slice_print()
    
    P2.time_evol(fx2,fy2,0.0,0.001)
    P2.time_slice_print()
    l+=1

plt.pyplot.plot(x2,y2)
plt.pyplot.ion()
plt.pyplot.plot(x,y,'r')
plt.pyplot.show()

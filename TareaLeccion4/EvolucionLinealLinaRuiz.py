import matplotlib.pyplot as plt
import numpy as np
from particle import Particle as particle

Carga1=1.0
p1=particle(0.0,0.0,0.0,0.0,0.0,0.0,20.0,Carga1)
x=[];y=[];z=[];vx=[]; vy=[]; vz=[]

Carga2=-1.0
p2=particle(1.0,0.0,0.0,0.0,0.0,0.0,20.0,Carga2)
x2=[];y2=[];z2=[];vx2=[]; vy2=[]; vz2=[]

BX=0.0
BY=0.0
BZ=10

i=0

while i<100000:
    x.append(p1.X); y.append(p1.Y); z.append(p1.Z)
    vx.append(p1.VX); vy.append(p1.VY); vz.append(p1.VZ)
    x2.append(p2.X); y2.append(p2.Y); z2.append(p2.Z)
    vx2.append(p2.VX); vy2.append(p2.VY); vz2.append(p2.VZ)
    p1.fuerza(p2.X,p2.Y,p2.Z,p2.Carga,BX,BY,BZ)
    p2.fuerza(p1.X,p1.Y,p1.Z,p1.Carga,BX,BY,BZ)
    p1.time_evol(p1.fx,p1.fy,p1.fz,0.0001)
    p2.time_evol(p2.fx,p2.fy,p2.fz,0.0001)
    #p1.tiempo_slice_print ()
    i+=1
plt.plot(x,y)
plt.hold(True)
plt.plot(x2,y2)
plt.show()

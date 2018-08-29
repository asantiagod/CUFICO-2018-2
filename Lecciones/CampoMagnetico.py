import matplotlib.pyplot as plt
from ParticleClass import Particle as Particle

P2=Particle(0.0,0.0,0.0,1.00,0.0,0.0,10.00,1.0)

i=0
x=[]; y=[]; z=[]
vx=[]; vy=[]
Bz=10.000

while i<100000:
    x.append(P2.X); y.append(P2.Y); z.append(P2.Z)
    vx.append(P2.VX); vy.append(P2.VY)
    fx=P2.Carga*P2.VY*Bz
    fy=-1.0*P2.Carga*P2.VX*Bz
    P2.time_evol(fx,fy,0.0,0.0001)
    P2.time_slice_print()
    i+=1

plt.plot(x,y)
plt.show()

import matplotlib.pyplot as plt
import numpy as np
from Particle import Particle as Particle
P1 = Particle(0.0, 0.0, 0.0, 0 , 0.0, 0.0, 10.00, 1.0)
P2 = Particle(1.0, 0.0, 0.0, 0, 0.0, 0.0, 10.00, 1.0)
i = 0
x1=[]; y1=[]; z1=[];
x2=[]; y2=[]; z2=[];
Bz=10.000
k=1#Por convenciencia

def norm(P1, P2):
	return np.sqrt((P2.X-P1.X)**2 + (P2.Y-P1.Y)**2 + (P2.Z-P1.Z)**2)

while(i<10000):
	r21 = norm(P1, P2)
	x1.append(P1.X); y1.append(P1.Y); z1.append(P1.Z)
	x2.append(P2.X); y2.append(P2.Y); z2.append(P2.Z)

	fx1 = P1.Q*P1.VY*Bz+k*P1.Q*P2.Q*(P1.X-P2.X)/(r21**3)
	fx2 = P2.Q*P2.VY*Bz+k*P1.Q*P2.Q*(P2.X-P1.X)/(r21**3)
	fy1 = -1.0*P1.Q*P1.VX*Bz+k*P1.Q*P2.Q*(P1.Y-P2.Y)/(r21**3)
	fy2 = -1.0*P2.Q*P2.VX*Bz+k*P1.Q*P2.Q*(P2.Y-P1.Y)/(r21**3)

	P1.Time_evol(fx1, fy1, 0.0, 0.01)
	P2.Time_evol(fx2, fy2, 0.0, 0.01)
	#P2.time_slice_print()
	i+=1

plt.plot(x1, y1)
plt.plot(x2, y2)
plt.show()
	

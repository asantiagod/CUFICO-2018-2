import matplotlib.pyplot as plt
import numpy as np
from CinematicaClases import Particle as Particle

P1=Particle(0.,0.,0.,0.,0.,0.,1.,1.)

P2=Particle(1.,0.,0.,0.,0.,0.,1.,-1.)

i=0.

Bz=5.
k=9

x1=np.array([])
y1=np.array([])
x2=np.array([])
y2=np.array([])

while i < 10000:
	x1=np.append(P1.X,x1)
	y1=np.append(P1.Y,y1)
	x2=np.append(P2.X,x2)
	y2=np.append(P2.Y,y2)
	
	r=np.sqrt(((P2.X-P1.X)**2.)+((P2.Y-P1.Y)**2.))

	f1x=P1.Carga*(((k*P2.Carga*(P1.X-P2.X))/(r**3.))+P1.VY*Bz)
	f1y=P1.Carga*(((k*P2.Carga*(P1.Y-P2.Y))/(r**3.))-P1.VX*Bz)
	f2x=P2.Carga*(((k*P1.Carga*(P2.X-P1.X))/(r**3.))+P2.VY*Bz)
	f2y=P2.Carga*(((k*P1.Carga*(P2.Y-P1.Y))/(r**3.))-P2.VX*Bz)

	#f1x=P1.Carga*(((k*P2.Carga*(P2.X-P1.X))/(r**3.)))
	#f1y=P1.Carga*(((k*P2.Carga*(P2.Y-P1.Y))/(r**3.)))
	#f2x=P2.Carga*(((k*P1.Carga*(P1.X-P2.X))/(r**3.)))
	#f2y=P2.Carga*(((k*P1.Carga*(P1.Y-P2.Y))/(r**3.)))
	
	P1.Time_evol(f1x,f1y,0.,.001)
	P2.Time_evol(f2x,f2y,0.,.001)

	i=i+1

plt.figure()
plt.plot(x1,y1)
plt.plot(x2,y2)
plt.show()

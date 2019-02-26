import matplotlib.pyplot as plt
import numpy as np
from ParticleClass import Particle as Particle

P1=Particle(0,0,0,0,0,0,10,1.)
P2=Particle(1,0,0,0,0,0,10,-1)

e0=8.85e-12
k=1/(4*np.pi*e0)
i=0
x1=[]; y1=[]; z1=[]
x2=[]; y2=[]; z2=[]
vx1=[]; vy1=[]
vx2=[]; vy2=[]

Bz=10.000


while i<10000:
	
	x1.append(P1.X); y1.append(P1.Y); z1.append(P1.Z)
	vx1.append(P1.VX); vy1.append(P1.VY)

	fx1=(P1.Carga*P2.Carga*k)*(P1.X-P2.X)/((P1.X-P2.X)**2+(P1.Y-P2.Y)**2+(P1.Z-P2.Z)**2)**3 +1.0*P1.Carga*P1.VY*Bz
	fy1=-1.0*P1.Carga*P1.VX*Bz+(P1.Carga*P2.Carga*k)*(P1.Y-P2.Y)/((P1.X-P2.X)**2+(P1.Y-P2.Y)**2+(P1.Z-P2.Z)**2)**3

	x2.append(P2.X); y2.append(P2.Y); z2.append(P2.Z)
	vx2.append(P2.VX); vy2.append(P2.VY)

	fx2=(P1.Carga*P2.Carga*k)*(P2.X-P1.X)/((P1.X-P2.X)**2+(P1.Y-P2.Y)**2+(P1.Z-P2.Z)**2)**3 +1.0*P2.Carga*P2.VY*Bz
	fy2=-1.0*P1.Carga*P1.VX*Bz+ (P1.Carga*P2.Carga*k)*(P2.Y-P1.Y)/((P1.X-P2.X)**2+(P1.Y-P2.Y)**2+(P1.Z-P2.Z)**2)**3
	
	P1.time_evol(fx1,fy1,0,0.01)
	P2.time_evol(fx2,fy2,0,0.01)
	
	i+=1

plt.figure(figsize=(20,20))
plt.title("Posicion de dos particulas con carga opuesta en el seno de un campo magnetico")
plt.plot(x1,y1,"m-", label="Particula cargada positivamente")
plt.plot(x2,y2,"k-", label="Particula cargada negativamente")
plt.legend(loc="upper left")
plt.xlabel("X")
plt.ylabel("Y")
#plt.show()
plt.savefig("Dos_Particulas_Cargadas.png")



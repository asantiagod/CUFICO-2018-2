
#Librerias importadas
import matplotlib.pyplot as plt
import numpy as np
#Clase importada
from ParticleClass import Particle as Particle 

P1=Particle(0.0,0.0,0.0,0.0,0.0,0.0,10.00,1.0) #Particula1 (x,y,z,vx,vy,vz,m,carga)
P2=Particle(1.0,0.0,0.0,0.0,0.0,0.0,10.00,-1.0) #Particula2 (x,y,z,vx,vy,vz,m,carga)


i=0
x1=[]; y1=[]; z1=[]
vx1=[]; vy1=[]
x2=[]; y2=[]; z2=[]
vx2=[]; vy2=[]


k=9e9 #Constante de Coulomb (N*m**2/C**2)
Bz=10.0 #Valor del campo magnetico constante en direccion z

while (i<10000):
	x1.append(P1.X);y1.append(P1.Y); z1.append(P1.Z)
	vx1.append(P1.VX);vy1.append(P1.VY)
	x2.append(P2.X); y2.append(P2.Y); z2.append(P2.Z)
	vx2.append(P2.VX);vy2.append(P2.VY)

	r= np.sqrt(((P1.X-P2.X)**2)+((P1.Y-P2.Y)**2)+((P1.Z-P2.Z)**2))
	
	Fe = k*P1.Carga*P2.Carga/(r)**3 #fuerza electrica
	
	
	fx1=Fe+P1.Carga*P1.VY*Bz
	fy1=Fe+(-1.00)*P1.Carga*P1.VX*Bz


	fx2=-Fe+P2.Carga*P2.VY*Bz #fuerza electrica con la misma magnitud pero en direccion contraria
	fy2=-Fe+(-1.00)*P2.Carga*P2.VX*Bz

	P1.time_evol(fx1,fy1,0.0,0.01)
	P1.time_slice_print()

	P2.time_evol(fx2,fy2,0.0,0.01)
	P2.time_slice_print()

	i+=1

#Para graficar
plt.plot(x1,y1,'b-')
plt.plot(x2,y2,'r-')
plt.grid()
plt.title('PARTICLE POSITION')
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.show()

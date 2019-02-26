from numpy import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from Clase_particula import Particula as Particula

e0= 8.8541878176*10**(-12)
P1= Particula(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 17)
P2= Particula(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, -17)

i=0
x1= []; y1= []; z1= []
x2= []; y2= []; z2= []
Bz= 10.0

while i<10000:
	x1.append(P1.X); y1.append(P1.Y); z1.append(P1.Z) 
	x2.append(P2.X); y2.append(P2.Y); z2.append(P2.Z)
	NR21= sqrt((P1.X-P2.X)**2+(P1.Y-P2.Y)**2+(P1.Z-P2.Z)**2)
	fx1= P1.Carga*P1.VY*Bz + (1/(4*pi*e0*NR21**3))*(P1.X-P2.X)*(P1.Carga*P2.Carga)
	fy1= -1.0*P1.Carga*P1.VX*Bz + (1/(4*pi*e0*NR21**3))*(P1.Y-P2.Y)*(P1.Carga*P2.Carga)
	fz1= (1/(4*pi*e0*NR21**3))*(P1.Z-P2.Z)*(P1.Carga*P2.Carga)	
	NR12= sqrt((P2.X-P1.X)**2+(P2.Y-P1.Y)**2+(P2.Z-P1.Z)**2)
	fx2= P2.Carga*P2.VY*Bz +(1/(4*pi*e0*NR12**3))*(P2.X-P1.X)*(P1.Carga*P2.Carga) 
	fy2= -1.0*P2.Carga*P2.VX*Bz +(1/(4*pi*e0*NR12**3))*(P2.Y-P1.Y)*(P1.Carga*P2.Carga)
	fz2= (1/(4*pi*e0*NR12**3))*(P2.Z-P1.Z)*(P1.Carga*P2.Carga)
	P1.Time_evol(fx1, fy1, fz1, 0.01)
	P2.Time_evol(fx2, fy2, fz2, 0.01)
	i+= 1

plt.style.use('classic')
fig= plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x1, y1, z1, linestyle= '-', linewidth=1.5, color= 'seagreen', label= r'$p_{1}$')
ax.plot3D(x2, y2, z2, linestyle= '-', linewidth=1.5, color= 'crimson', label= r'$p_{2}$')
leg = ax.legend(frameon= False, loc= 'lower left')
plt.title(r'$Partículas\ cargadas\ sometidas\ a\ un\ campo\ magnético\ externo''$')
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.show()

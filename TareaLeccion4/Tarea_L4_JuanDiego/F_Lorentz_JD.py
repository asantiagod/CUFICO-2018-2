import numpy as np
import matplotlib.pyplot as plt
import Classes as C
from mpl_toolkits.mplot3d import Axes3D
from scipy.constants import epsilon_0


K = 1./(4*np.pi*epsilon_0)
B = [0., 0., 10.] #Magnetic field
t = 0.01

P1 = C.Particle(0.,0.,0., 0.,0.,0., 10., -1.) #Particle 1
P2 = C.Particle(1.,0.,0., 0.,0.,0., 10., 1.) #Particle 2  


x1=[]; y1=[]; z1=[];
x2=[]; y2=[]; z2=[];


def Campo(p1, p2): #p1 es la carga que genera el campo, p2 es la carga que siente el campo
	r = p1.Distancia(p2)
	
	Ex = p1.Carga * (p2.X - p1.X) * K / r**3
	Ey = p1.Carga * (p2.Y - p1.Y) * K / r**3
	Ez = p1.Carga * (p2.Z - p1.Z) * K / r**3
	
	return [Ex, Ey, Ez]
	
def Fuerza(p1, p2): #p1 es la carga acelerada debido al campo generado por p2 
    Fx = p1.Carga * (Campo(p2,p1)[0] + (p1.VY * B[2] - p1.VZ * B[1]) )
    Fy = p1.Carga * (Campo(p2,p1)[1] + (p1.VZ * B[0] - p1.VX * B[2]) )
    Fz = p1.Carga * (Campo(p2,p1)[2] + (p1.VX * B[1] - p1.VY * B[0]) )
    
    return [Fx, Fy, Fz]	
	
	
i = 0 
while i < 10000:

    P1.Time_evol(*Fuerza(P1, P2),t)    
    P_iter = C.Particle(*P1.Estado_anterior)    
    P2.Time_evol(*Fuerza(P2, P_iter), t)    
    
    x1.append(P1.X); y1.append(P1.Y) ; z1.append(P1.Z)
    x2.append(P2.X); y2.append(P2.Y) ; z2.append(P2.Z)
    i+=1
    

fig = plt.figure(figsize = (8,8))
ax = Axes3D(fig)
ax.plot(x1,y1,z1, label = "Particula 1", color = 'tomato')
ax.plot(x2,y2,z2, label = "Particula 2", color = 'darkblue')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('Trayectoria de las particulas')
plt.legend()
plt.show()

"""
plt.plot(x1,y1, label = "Particula 1") 
plt.plot(x2,y2, label = "Particula 2")
plt.legend()
plt.grid()
plt.show()
"""

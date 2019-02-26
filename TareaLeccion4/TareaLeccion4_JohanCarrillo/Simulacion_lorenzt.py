import numpy as np
import Clases as C
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


k = 1 / ( 4 * np.pi * 8.85e-12)
B = (0,0,10)                        #Se define el valor del campo magnetico
i = 0                               #Se inicializa el contador
dt = 0.001                          #Pasos de tiempo


Particula_1 = C.Particle(0., 0., 3., 0., 0., 0., 10.0, 1.0)
Particula_2 = C.Particle(1.0, 0., -3., 0., 0., 0., 10.0, -1.0) 


Pos_p1 = [[Particula_1.X], [Particula_1.Y], [Particula_1.Z]]
Pos_p2 = [[Particula_2.X], [Particula_2.Y], [Particula_2.Z]]


def Intensidad(p1, p2):
    '''Esta funcion calcula la intensidad de cada componente del campo
    electrico generado por la particula 1 en la posicion de la particula 
    2'''

    r = p1.Distancia(p2)
	
    Ex = p1.Carga * (p2.X - p1.X) * k / r**3
    Ey = p1.Carga * (p2.Y - p1.Y) * k / r**3
    Ez = p1.Carga * (p2.Z - p1.Z) * k / r**3

    return [Ex, Ey, Ez]
	
	
def F_lorenzt(p1, p2):
    '''Esta funcion calcula la fuerza de Lorentz sobre la particula 1 debido
    al campo elec que tiene en cuenta el
    campo electrico, magnetico y las velocidades de las particulas'''

    Fx = p1.Carga * (Intensidad(p2,p1)[0] + (p1.Vy * B[2] - p1.Vz * B[1]))
    Fy = p1.Carga * (Intensidad(p2,p1)[1] + (p1.Vz * B[0] - p1.Vx * B[2]))
    Fz = p1.Carga * (Intensidad(p2,p1)[2] + (p1.Vx * B[1] - p1.Vy * B[0]))

    return [Fx, Fy, Fz, dt]



while(i <= 10000):
    '''Este ciclo realiza la evolucion del sistema 10 mil veces y guarda
    las variables de estado para cada paso de tiempo'''

    #Se evoluciona P1 y se guarda el estado    
    Particula_1.time_evol(*F_lorenzt(Particula_1, Particula_2))

    Pos_p1[0].append(Particula_1.X)
    Pos_p1[1].append(Particula_1.Y)
    Pos_p1[2].append(Particula_1.Z)

    #Se evoluciona P2 y se guarda el estado
    Particula_2.time_evol(*F_lorenzt(Particula_2, C.Particle(*Particula_1.Estado_anterior)))

    Pos_p2[0].append(Particula_2.X)
    Pos_p2[1].append(Particula_2.Y)
    Pos_p2[2].append(Particula_2.Z)

    i += 1

#A cntinuacion se procede a realizar el grafico
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot(Pos_p1[0], Pos_p1[1], Pos_p1[2], label='Particula 1', c='b')
ax.plot(Pos_p2[0], Pos_p2[1], Pos_p2[2], label='Particula 2', c='g')
ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title('Dos particulas cargadas en un campo magnetico uniforme')
ax.legend(loc='best')
plt.show()


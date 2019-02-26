from numpy import pi
import Clases as C
import matplotlib.pyplot as plt 
from mpl_toolkits import mplot3d


#Variables globales

k = 1 / ( 4 * pi * 8.85e-12)
B = (0,0,10)
i = 0
dt = 0.01

# se definen dos objeto del tipo particula 
# con condiciones iniciales 

Particula_1 = C.Particle(0., 0. ,0. , 0., 0., 0., 1.0, 1.0)
Particula_2 = C.Particle(1., 0. ,0. , 0., 0., 0., 1.0, -1.0) 

# se definene dos listas que guardaran la evolucion de las posiciones de las
# particulas y se iniciaizan con las posiciones iniciales.

Pos_p1 = [[Particula_1.X], [Particula_1.Y], [Particula_1.Z]]
Pos_p2 = [[Particula_2.X], [Particula_2.Y], [Particula_2.Z]]


def Intensidad(p1, p2):
    '''Esta funcion utiliza los atributos de los objetos p1 y p2 y calcula 
    la intensidad de campo electrico en la posicion de p2 debido a la presencia
    de la particula p1. Retorna una lista con cada componente del campo '''    
    
    r = p1.Distancia(p2)

    Ex = p1.Carga * (p2.X - p1.X) * k / r**3
    Ey = p1.Carga * (p2.Y - p1.Y) * k / r**3
    Ez = p1.Carga * (p2.Z - p1.Z) * k / r**3
	
    return [Ex, Ey, Ez]
	
	
def F_lorenzt(p1, p2, dt):
    
    ''' Esta funcion utiliza los atributos de p1 y p2 y la funcion Intensidad 
    para calcular la fuerza de lorenzt que actua sobre p1 debido a p2. Retorna 
    una lista con las componentes del campo y el paso temporal para hacer una 
    evolucion con el metodo "time_evol" de la clase Particle. '''
    
    Fx = p1.Carga * ( Intensidad(p2,p1)[0] + (p1.Vy * B[2] - p1.Vz * B[1]) )
    Fy = p1.Carga * ( Intensidad(p2,p1)[1] + (p1.Vz * B[0] - p1.Vx * B[2]) )
    Fz = p1.Carga * ( Intensidad(p2,p1)[2] + (p1.Vx * B[1] - p1.Vy * B[0]) )

    return [Fx, Fy, Fz, dt]


# se evoluciona el estado de la particula_1 y particula_2 en pasos de tiempo
# dt = 0.001 10000 veces.

while(i <= 10000):
    
    Particula_1.time_evol(*F_lorenzt(Particula_1, Particula_2, dt))
    
    Pos_p1[0].append(Particula_1.X)
    Pos_p1[1].append(Particula_1.Y)
    Pos_p1[2].append(Particula_1.Z)
    
    # se utiliza P_iter como particula auxiliar en el ciclo para evolucionar p2
    # con el estado anterior a la evolucion de p1, con esto se garantiza que 
    # ambas particulas evolucionan simultaneamente.
    
    P_iter = C.Particle(*Particula_1.Estado_anterior) 
    
    Particula_2.time_evol(*F_lorenzt(Particula_2, P_iter, dt))
    
    Pos_p2[0].append(Particula_2.X)
    Pos_p2[1].append(Particula_2.Y)
    Pos_p2[2].append(Particula_2.Z)
    
    i += 1
    
    
    
# Grafica de la trayectoria de la particula_1 y la particula_2
fig = plt.figure()
ax = plt.axes(projection='3d')

ax.plot3D(Pos_p1[0], Pos_p1[1], Pos_p1[2], label ="Trayectoria de la particula_1")
ax.plot3D(Pos_p2[0], Pos_p2[1], Pos_p2[2], label ="Trayectoria de la particula_2")
plt.legend(loc = "best")
ax.scatter(0.,0.,0.)
ax.scatter(1.,0.,0., color ="red")

plt.title("Trayectoria de dos particulas con carga q1 = %.1f y q2 = %.1f"%(
            Particula_1.Carga, Particula_2.Carga))
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")

plt.show()    





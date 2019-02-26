class Particle:
    #atributos
    carga = True


    #instancias (metodos)
    def __init__(self, x, y, z, vx, vy, vz, m, carga):
        '''Esta funcion asigna los valores de estado de la particula y 
        guarda el estado anterior en un arreglo que se necesitara luego'''

        self.X = x              #Posiciones de la particula
        self.Y = y
        self.Z = z
        self.Vx = vx            #Velocidades de la particula
        self.Vy = vy
        self.Vz = vz
        self.M = m              #Masa de la particula
        self.Carga = carga      #Carga de la particula
        self.Estado_anterior = [self.X, self.Y, self.Z, self.Vx, self.Vy, self.Vz, self.M, self.Carga]


    def Distancia(self, Particle):
        '''Esta funcion mide la distancia entre las particulas, esta es 
        necesaria para calcular la magnitud del campo electrico'''

        return ((self.X - Particle.X)**2 + (self.Y - Particle.Y)**2 + (self.Z - Particle.Z)**2)**0.5

    def pos_evol(self, x, v, a, t):
        '''Esta funcion calcula la posicion de la particula para un 
        instante de tiempo'''
            
        return x + (v*t) + (0.5*a*t**2)

    def vel_evol(self, v, a, t):
        '''Esta funcion calcula la velocidad de la particula para un 
        instante de tiempo'''

        return v + a*t
    
    def time_evol(self, fx, fy, fz, t):
        '''Esta funcion calcula las variables de estado de la particula
        para el instante de tiempo siguiente'''

        self.Estado_anterior = [self.X, self.Y, self.Z, self.Vx, self.Vy, self.Vz, self.M, self.Carga]
        self.X = self.pos_evol(self.X, self.Vx, fx/self.M, t)
        self.Y = self.pos_evol(self.Y, self.Vy, fy/self.M, t)
        self.Z = self.pos_evol(self.Z, self.Vz, fz/self.M, t)
        self.Vx = self.vel_evol(self.Vx, fx/self.M, t)
        self.Vy = self.vel_evol(self.Vy, fy/self.M, t)
        self.Vz = self.vel_evol(self.Vz, fz/self.M, t)


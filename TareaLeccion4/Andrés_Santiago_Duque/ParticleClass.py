from numpy import sqrt
from scipy.constants import epsilon_0, pi

class Vector:
    
    def __init__(self, vec_X=0., vec_Y=0., vec_Z=0.):
        self.X = vec_X
        self.Y = vec_Y
        self.Z = vec_Z
        
    def Update(self, vec_X, vec_Y, vec_Z):
        self.X = vec_X
        self.Y = vec_Y
        self.Z = vec_Z
    
    
def LorentzForce(Q, E, B, V):
    """
    Fuerza de Lorentz sobre una partícula puntual
    """
    if not isinstance(E, Vector) or not isinstance(B, Vector) or not isinstance(V, Vector):
            raise TypeError("El tipo de argumentos debe ser {0}".format(Vector))
    F = Vector()
    F.X = Q*(E.X + V.Y*B.Z - V.Z*B.Y)
    F.Y = Q*(E.Y + V.Z*B.X - V.X*B.Z)
    F.Z = Q*(E.Z + V.X*B.Y - V.Y*B.X)
    return F
        

class Particle:
    #Atributos
    cargada =  True
    
    #Instancias (metodos)
    def __init__(self, x, y, z, vx, vy, vz, m, carga): #Funcion que se aplica sobre la classe misma (self)
        self.X = x
        self.Y = y
        self.Z = z
        self.VX = vx
        self.VY = vy
        self.VZ = vz
        self.M = m
        self.Carga = carga
        
        #vectores
        self.Pos = Vector(self.X, self.Y, self.Z)
        self.Vel = Vector(self.VX, self.VY, self.VZ)

    def Pos_evol(self,xi,vi,a,t):
        return xi+(vi*t)+(0.5*a*(t**2))

    def Vel_evol(self,vi,a,t):
        return vi+(a*t)

    def time_evol(self, fx, fy, fz,t):
        self.X = self.Pos_evol(self.X,self.VX,fx/self.M,t)
        self.Y = self.Pos_evol(self.Y,self.VY,fy/self.M,t)
        self.Z = self.Pos_evol(self.Z,self.VZ,fz/self.M,t)
        self.VX = self.Vel_evol(self.VX,fx/self.M,t)
        self.VY = self.Vel_evol(self.VY,fy/self.M,t)
        self.VZ = self.Vel_evol(self.VZ,fz/self.M,t)
        
        # Actualizar vectores
        self.Pos.Update(self.X, self.Y, self.Z)
        self.Vel.Update(self.VX, self.VY, self.VZ)

    def time_slice_print(self):
        print ("x={0:.2f}, y={1:.2f}, z={2:.2f}, vx={3:.2f}, vy={4:.2f}, " \
               "vz={5:.2f}".format(self.X,self.Y,self.Z,self.VX,self.VY,self.VZ))
        
    def Electric_Field(self, pos):
        """
        Campo electrico debido a la carga de la partícula en 
        una posición específica.
        Retorna un vector con las componentes del campo.
        """
        if not isinstance(pos, Vector):
            raise TypeError("El tipo de argumento debe ser {0}".format(Vector))
        
        r_3 = (sqrt(((pos.X - self.X)**2 + (pos.Y - self.Y)**2 + (pos.Z - self.Z)**2)))**3
        k = self.Carga/(4.*pi*epsilon_0*r_3)
        E = Vector()
        E.X = k*(pos.X - self.X)
        E.Y = k*(pos.Y - self.Y)
        E.Z = k*(pos.Z - self.Z)        
        return E
        
        
        
        
    

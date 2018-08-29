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

    def time_slice_print(self):
        print "x={0:.2f}, y={1:.2f}, z={2:.2f}, vx={3:.2f}, vy={4:.2f}, vz={5:.2f}".format(self.X,self.Y,self.Z,self.VX,self.VY,self.VZ)

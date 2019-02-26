import numpy as np
class Particle:
    #Atributos
    cargada =  True
    #Instancias (metodos)
    def __init__(self, x, y, z, vx, vy, vz, m, carga): #Funcion que se aplica sobre la classe misma (sel
        self.X = x
        self.Y = y
        self.Z = z
        self.VX = vx
        self.VY = vy
        self.VZ = vz
        self.M = m
        self.Carga = carga
        self.fx=0.0
        self.fy=0.0
        self.fz=0.0
    def pos_evol(self,xi,vi,a,t):
        return xi + (vi*t) + (0.5*a*(t**2))
    def vel_evol(self, vi,a,t):
        return vi+(a*t)
    def time_evol(self,fx,fy,fz,t):
        self.X=self.pos_evol(self.X,self.VX,self.fx/self.M,t)
        self.Y=self.pos_evol(self.Y,self.VY,self.fy/self.M,t)
        self.Z=self.pos_evol(self.Z,self.VZ,self.fz/self.M,t)
        self.VX=self.vel_evol(self.VX, self.fx/self.M,t)
        self.VY=self.vel_evol(self.VY, self.fy/self.M,t)
        self.VZ=self.vel_evol(self.VZ, self.fz/self.M,t)
    def fuerza(self, x2, y2, z2,Carga2,BX,BY,BZ):
        r=np.array([self.X-x2,self.Y-y2,self.Z-z2])
        normar=(np.dot(r,r))**(1/2)
        B=np.array([BX,BY,BZ])
        vel=np.array([self.VX, self.VY, self.VZ])
        f=np.array((1.0*self.Carga*Carga2/normar**3)*r+self.Carga*np.cross(vel,B))
        self.fx=f[0]
        self.fy=f[1]
        self.fz=f[2]
    def tiempo_slice_print(self):
        print("x={0:.2f},y={1:.2f},z={2:.2f},vx={3:.2f},vy={4:.2f},vz={5:.2f}" .format(self.X, self.Y, self.Z, self.VX, self.VY, self.VZ))

        

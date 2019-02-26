class Particle:
	#atributos
	carga = True
	
	#instancias (metodos)
	def __init__(self, x, y, z, vx, vy, vz, m, carga):# funcion que se aplica sobre la clase misma(self)
		self.X = x
		self.Y = y
		self.Z = z
		self.Vx = vx
		self.Vy = vy
		self.Vz = vz
		self.M = m
		self.Carga = carga
		self.Estado_anterior = [self.X, self.Y, self.Z, self.Vx, self.Vy, self.Vz, self.M, self.Carga]
		
	def Distancia(self, Particle):
	    return ( (self.X - Particle.X)**2 +
	             (self.Y - Particle.Y)**2 + 
	             (self.Z - Particle.Z)**2 )**0.5
	
	def pos_evol(self, x, v, a, t):
		return x + (v*t) + (0.5*a*t**2)
		
	def vel_evol(self, v, a, t):
		return v + a*t
		
	def time_evol(self, fx, fy, fz, t):
	    self.Estado_anterior = [self.X, self.Y, self.Z, self.Vx, self.Vy, self.Vz, self.M, self.Carga]
	    self.X = self.pos_evol(self.X, self.Vx, fx/self.M, t)
	    self.Y = self.pos_evol(self.Y, self.Vy, fy/self.M, t)
	    self.Z = self.pos_evol(self.Z, self.Vz, fz/self.M, t)
	    self.Vx = self.vel_evol(self.Vx, fx/self.M, t)
	    self.Vy = self.vel_evol(self.Vy, fy/self.M, t)
	    self.Vz = self.vel_evol(self.Vz, fz/self.M, t)
		
	def time_slice_print(self):
		print("x = {0:.2f}, y = {1:.2f}, z = {2:.2f}".format(self.X, self.Y, self.Z))
		
		

#
# Andrés Santiago Duque Escobar
#


from ParticleClass import Particle, Vector, LorentzForce
from matplotlib.pyplot import plot, show


x1 = []
y1 = []
x2 = []
y2 = []
t = []

#Partículas
p1 = Particle(0.,0.,0.,0.,0.,0.,10.,0.001)
p2 = Particle(1.,0.,0.,0.,0.,0.,10.,-0.001)

#Campo magnético
B = Vector(0.,0.,10.)

x1.append(p1.X)
y1.append(p1.Y)
x2.append(p2.X)
y2.append(p2.Y)
t.append(0.)
step = 0.0001
for i in range(263):
    #Campo electrico    
    E1 = p2.Electric_Field(p1.Pos) #Sobre p1 debido a p2
    E2 = p1.Electric_Field(p2.Pos) #Sobre p2 debido a p1
    
    #Fuerzas 
    #F1 = LorentzForce(p1.Carga,Vector(),B,p1.Vel) #Sobre p1
    F1 = LorentzForce(p1.Carga,E1,B,p1.Vel) #Sobre p1 
    F2 = LorentzForce(p2.Carga,E2,B,p2.Vel) #Sobre p2
    #F2 = LorentzForce(p2.Carga,Vector(),B,p2.Vel) #Sobre p2
    
    #Evolución temporal
    p1.time_evol(F1.X, F1.Y, F1.Z, step)
    p2.time_evol(F2.X, F2.Y, F2.Z, step)
    
    x1.append(p1.X)
    y1.append(p1.Y)
    x2.append(p2.X)
    y2.append(p2.Y)
    t.append(t[-1]+step)


p1.time_slice_print()
p2.time_slice_print()

plot(x1,y1,'r')
plot(x2,y2)
show()

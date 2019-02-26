import clase as c
import numpy as np
import matplotlib.pylab as plt

P1 = c.Particle(0.0,0.0,0.0,0.0,0.0,0.0,1,1)
P2 = c.Particle(1.0,0.0,0.0,0.0,0.0,0.0,1,-1)

k = (0.25*np.pi*8.85e-12)

def Fl(P1,P2):

    r = np.sqrt((P1.X - P2.X)**2 + (P1.Y - P2.Y)**2 + (P1.Z - P2.Z)**2)

    FX = P1.Carga*((k*P2.Carga*(P1.X - P2.X)/r**3) + P1.VY*10)    
    FY = P1.Carga*((k*P2.Carga*(P1.Y - P2.Y)/r**3) - P1.VX*10)
    FZ = P1.Carga*((k*P2.Carga*(P1.Z - P2.Z)/r**3) + 0)
    
    return FX, FY, FZ


PosX1 = []
PosY1 = []
PosZ1 = []

PosX2 = []
PosY2 = []
PosZ2 = []

i = 1
while i < 10000:
    dt = 0.01

    P1.Time_evol(Fl(P1,P2)[0], Fl(P1,P2)[1], Fl(P1,P2)[2], dt)
    P2.Time_evol(Fl(P2,P1)[0], Fl(P2,P1)[1], Fl(P2,P1)[2], dt)
    
    PosX1.append(P1.X)
    PosY1.append(P1.Y)
    PosZ1.append(P1.Z)
    
    PosX2.append(P2.X)
    PosY2.append(P2.Y)
    PosZ2.append(P2.Z)
    
    i = i + 1
    
plt.plot(PosX1,PosY1, label = r'$Carga\ positiva\ q1$')
plt.plot(PosX2,PosY2, label = r'$Carga\ negativa\ q2$')
plt.title(r'$Trayectoria\ de\ dos\ cargas\ bajo\ efectos\ de\ un\ campo\ B \hat{k}$')
plt.ylabel(r'$ Y $')
plt.xlabel(r'$ X $')
plt.grid()
plt.savefig('TareaL4.png')
plt.legend(loc = ('upper right') ) 
plt.show()

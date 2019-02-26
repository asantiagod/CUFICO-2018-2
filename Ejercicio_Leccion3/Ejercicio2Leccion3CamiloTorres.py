#Importa las funciones de las librerias
from numpy import sqrt, pi, exp, linspace, load,array, zeros
import matplotlib.pyplot as plt

def function(x, amp1, cen1, wid1, amp2, cen2, wid2,inter,pen): #Define la suma de dos gaussianas y una linea recta
    return amp1*exp(-(x-cen1)**2/wid1) + amp2*exp(-(x-cen2)**2/wid2) + pen*x + inter 

#Carga los datos de los archivos compartidos
x = load("x_spectra.npy")
y = load("y_spectra.npy")

#Para realizar el fit
from scipy.optimize import curve_fit
init_vals = [120,10,3,130,30,5,100,1] #Condiciones iniciales para [amp1, cen1, wid1, amp2, cen2, wid2,inter,pen]
best_vals, covar = curve_fit(function, x, y, p0=init_vals)
print(best_vals)

#Para graficar
plt.scatter(x, y)
plt.plot(linspace(0,100,1000),function(linspace(0,100,1000),best_vals[0],best_vals[1],best_vals[2],best_vals[3],best_vals[4],best_vals[5],best_vals[6],best_vals[7]),"r-")
plt.show()

"""
Despues de realizar esta actividad se puede llegar a dos conclusiones:
1. Para realizar el fiteo es necesario observar el comportamiento de los datos y construir la función que mejor se adapte al problema
2. Los valores iniciales son de vital importancia para que el fiteo sea exitoso, estos se deben ser aproximados a los valores reales y tomarlos de los datos teóricos
"""
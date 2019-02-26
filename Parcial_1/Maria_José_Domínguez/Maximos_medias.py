import numpy as np

N = [] #para guardar el numero de n
Xmax = [] #para guardar los valores máximos

for i in range(5,65,5): #carga los archivos y a cada uno le halla el valor máximo, guardándolos en el array
  X = np.loadtxt('datos_n%i.txt'%(i), unpack = True)
  N.append(i)
  max = np.amax(X)
  Xmax.append(max)

Med = np.array([5.21867e-03, 5.16453e-03, 5.26250e-03, 5.18952e-03, 5.24915e-03, 5.21508e-03, 5.25829e-03, 5.21122e-03, 5.24649e-03, 5.26837e-03, 5.11963e-03, 5.17359e-03])
#los valores medios de las distribuciones fueron tomados del fit hecho con pyROOT
#para guardar los datos en un archivo de texto para su uso en google colab:
np.savetxt('maximos.txt', np.column_stack((N,Xmax)))
np.savetxt('medias.txt', np.column_stack((N,Med)))

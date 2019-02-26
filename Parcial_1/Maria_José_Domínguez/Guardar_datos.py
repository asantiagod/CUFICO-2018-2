import numpy as np
import commands as cm

'''
para guardar los datos se corre 500 veces por cada n (el cual va cambiando de 5 en 5) el script medida tiempo,
este ejecuta el juego de la vida y entrega el tiempo de ejecución con mayor precisión al que entrega el 
comando time, ya que al remover las pausas entre los cambios de estado del sistema el tiempo está en el rango de
los milisegundos. Los datos son guardados en archivos de texto diferentes para cada n
'''

for i in xrange(5,65,5):
	data = open('datos_n%i.txt'%(i),'w')
	for j in xrange(500):
		dato = cm.getoutput('bash medidatiempo.sh ')
		print >> data,dato
	data.close()

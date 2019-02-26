from time import time
t0=time()
b=1.001
while b<10000:
	b*=1.001

print (b)
t1=time()
tiempo_ejecucion =t1-t0
print ("Execution Time: ",tiempo_ejecucion) #En segundos
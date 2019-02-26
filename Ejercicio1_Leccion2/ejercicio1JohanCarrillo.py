from time import time

tiempo_inicial = time() 
 
b = 1.001
while b<10000:
	b*=1.001
	print(b)

 
tiempo_final = time() 
 
tiempo_ejecucion = tiempo_final - tiempo_inicial

print("el tiempo de ejecucion es: ", tiempo_ejecucion)

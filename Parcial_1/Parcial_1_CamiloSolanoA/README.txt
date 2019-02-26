Inicialmente se debe compilar el código c.cpp y ejecutar el archivo .out.

Al ejecutar el archivo .out, si no se introducen parámetros el programa pide las dimensiones manualmente (Punto 1.).

El código se detiene cuando se llega a un ciclo de periodo 3 o cuando el número de pasos supera el valor de la dimensión al cuadrado (Punto 2.).

Para la generación de datos (Punto 3), el archivo .out se ejecuta con los siguientes parámetros: mínima dimensión, máxima dimensión, numero de datos por dimensión, nombre de archivo de salida de datos, si/no graficar sistema en consola (0 o 1).

Ejemplo:
$ ./a.out 5 60 500 datos.txt 0

El archivo datos.txt se generó por medio de este último comando.

El notebook de Ipython p.ipynb lee el archivo datos.txt y genera los resultados requeridos(Puntos 4 a 7).

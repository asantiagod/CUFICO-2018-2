// Johan Alexis Carrillo Toro - 1214734681

#include <iostream>   //Libreria basica de input/output
#include <cstdlib>    //Libreria estandar de utilidades
#include <vector>     //Inicia un vector
#include <unistd.h>   #

using namespace std;

class Mapa
{
public:                                         //Variables que pueden ser usadas por todas las funciones de la clase
  int fil;                                      //Numero de filas elegido por el usuario
  int col;                                      //Numero de columnsa elegido por el usuario
  int vecinos;                                  //Declara el entero que va a ser el contador de vecinos
  vector<vector<int> > mapa;                    //Crea un vector que contiene vectores [matriz] hecho de enteros y se llama mapa

//Se definen las funciones que usa la clase la clase

  Mapa(int f, int c);
  void dibujar();                               //Void es una funcion que no retorna nada
  int analizarVecinos(int posf, int posc);      //Empieza con int porque esta funcion retorna un entero
  void ciclo();
};

//Se procede a dar la descripcion de las funciones

Mapa::Mapa(int f, int c)                        //Define la funcion mapa de la clase Mapa que lo que hace es darle el tamaño a la matriz y rellenarla
{
  fil = f;
  col = c;
  mapa.resize(fil);                             //Le da a mapa el numero de filas que va tener
  for(int i=0; i<mapa.size(); i++)              //Este for es para poner el numero de columnas
    {
      mapa[i].resize(col);                      //A cada elemento de mapa [el vector que es la primera fila] se le da su tamaño que es el numero de columnas 
    }
  
  for(int f=0; f<fil; f++)                      //Este for rellena la matriz de numeros aleatorios
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%2;                      //rand es un generador aleatorio de enteros, se le saca el modulo para que los numeros sean entre cero y uno
        }
    }
}

void Mapa::dibujar()                            //Funcion que imprime el mapa
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1)                          //Si la celula vive pinta un *
	    cout << "* ";
	  else
	    cout << ". ";                              //Si la celula muere punta un .
        }
      cout << "\n";                              //Si la fila se acaba baja a la siguiente
    }
}

int Mapa::analizarVecinos(int posf, int posc)    //Esta funcion revisa uno a uno las casillas al rededor del elemento en cuestion y retorna al final el numero de vecinos vivos
{
  vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;
            //Si la fila y columna anterior [arriba e izquierda] existen se mira si en la diagonal superior izquierda hay un vecino vivo
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos++;
            //Si la fila anterior [la de arriba] existe se mira si en el elemento superior central hay un vecino vivo
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;
            //Si la fila anterior [la de arriba] y la columna siguiente [la de derecha] existen se mira si hay un vecino en el elemento de la diagonal superior derecha
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos++;
            //Si la columna anterior existe [la de la izquierda] se mira si hay un vecino vivo en el elemento izquierdo central
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos++;
            //Si existe la columna siguiente [la de derecha] se mira si hay un vecino vivo en el elemento derecho central
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos++;
            //Si existe la fila siguiente [la de abajo] y la columna anterior [la de la izquierda] mira si hay un vecino vivo en el elemento de la diagonal inferior izquierda
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos++;
            //Si existe la fila siguiente [la de abajo] mira si hay un vecino vivo en el elemento inferior central
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos++;
            //Si existe la fila siguiente [la de abajo] y la columna siguiente [la de la derecha] mira si hay un vecino vivo en el elemento diagonal superior derecho
  return vecinos;
}

void Mapa::ciclo()                             //Esta funcion me hace el paso siguiente del ciclo [operador evolucion]
{
  vector<vector<int> > nueva_conf = mapa;      //Se crea una nueva matriz con los elementos de la vieja
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos = analizarVecinos(f, c);     //Recorre todas las filas y las columnas y va analizando los vecinos para cada elemento
	           //Condiciones por si la celula esta muerta
    if(mapa[f][c] == 0)
            {
	      if(vecinos == 3)
		nueva_conf[f][c] = 1;                      //Si la celula esta muerda y el numero de vecinos vivos es igual a 3 cambia la casilla en la matriz nueva a 1 [revive la celular] 
	      else
		nueva_conf[f][c] = 0;                      //Si la celular esta muerta y no tiene 3 vecinos vivos se deja la casilla en cero [se deja muerta]
            }
             //Condiciones por si la celula esta viva
	  if (mapa[f][c] == 1)
            {
	      if(vecinos == 2 || vecinos == 3)       //Si la celula esta viva y tiene 2 o 3 vecinos cambia la casilla de la matriz nueva por un 1 [revive la celula]
		nueva_conf[f][c] = 1;
	      else
		nueva_conf[f][c] = 0;                      //Si la celular esta viva pero no tiene 2 o 3 vecinos vivos cambia la casilla en la matriz nueva por un 0 [la mata]
            }
        }
    }
  
  mapa = nueva_conf;                           //Me establece la nueva matriz como la vieja
}

int main()
{
  srand(time(NULL));                           //Crea u numero aleatorio, le provee la semilla a srand usando el reloj interno del computador
  Mapa mapa(50, 50);                           //Llama la funcion mapa de la clase Mapa y le da el numero de filas y columnas deseado
  while(1)
    {
      mapa.dibujar();                          //Pinta la matriz
      usleep(100000);                          //usleep establece un tiempo de espera [en microsegundos] para cambiar de contador en el ciclo while
      system("clear");                         //limpia la consola para que la matriz siga saliendo en la misma parte
        mapa.ciclo();                          //Evoluciona ma matriz
    }
}

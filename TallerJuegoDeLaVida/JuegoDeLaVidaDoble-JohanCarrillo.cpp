// Johan Alexis Carrillo Toro - 1214734681
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

class Mapa
{
public:                                         // Variables que pueden ser usadas por fuera de la clase
  int fil;                                      // Numero de filas elegido por el usuario
  int col;                                      // Numero de columnsa elegido por el usuario
  int vecinos1;                                 // Numero de vecinos de tipo 1
  int vecinos2;                                 // Numero de vecinos de tipo 2
  vector<vector<int> > mapa;                    // Crea un vector que contiene vectores [matriz] hecho de enteros y se llama mapa

// Se definen funciones que se usaran en la clase de la clase

  Mapa(int f, int c);
  void dibujar();                               // Void es una funcion que no retorna nada
  int analizarVecinos(int posf, int posc);      // Empieza con int porque esta funcion retorna un entero
  void ciclo();
};

// Se procede a dar la definicion de las funciones

Mapa::Mapa(int f, int c)                        // Define la funcion mapa de la clase Mapa que lo que hace es darle el tamaño a la matriz y rellenarla
{
  fil = f;
  col = c;
  mapa.resize(fil);                             // Le da a mapa el numero de filas que va tener
  for(int i=0; i<mapa.size(); i++)              // Este for es para poner el numero de columnas
    {
      mapa[i].resize(col);                      // A cada elemento de mapa [el vector que es la primera fila] se le da su tamaño que es el numero de columnas 
    }
  
  for(int f=0; f<fil; f++)                      // Este for rellena la matriz de numeros aleatorios
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%3;                      // rand es un generador aleatorio de enteros, se genera un mapa aleatorio y se saca el modulo para que los elementos esten entre 0 y 2
        }
    }
}

void Mapa::dibujar()                            // Funcion que imprime el mapa
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1)                          // Si la celula 1 vive pinta un *
	    cout << "* ";
	  else if(mapa[f][c] == 2)
      cout << "# ";                               // Si la celula 2 vive pinta un #
    else
	    cout << ". ";                              // Si la celula muere punta un .
        }
      cout << "\n";                              // Si la fila se acaba baja a la siguiente
    }
}

int Mapa::analizarVecinos(int posf, int posc)    // Esta funcion revisa uno a uno las casillas al rededor del elemento en cuestion y calcula al final el numero de vecinos 1 y 2 vivos
{
  vecinos1 = 0;
  vecinos2 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos1++;
    else if (mapa[posf-1][posc-1] == 2)
      vecinos2++;
            // Si la fila y columna anterior [arriba e izquierda] existen, se mira si en la diagonal superior izquierda hay un vecino vivo y de que tipo es
  #include <iostream>

  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos1++;
    else if (mapa[posf-1][posc] == 2)
      vecinos2++;
            // Si la fila anterior [la de arriba] existe se mira si en el elemento superior central hay un vecino vivo de tipo 1 o 2
  
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos1++;
    else if (mapa[posf-1][posc+1] == 2)
      vecinos2++;
            // Si la fila anterior [la de arriba] y la columna siguiente [la de derecha] existen se mira si hay un vecino vivo de tipo 1 o 2 en el elemento de la diagonal superior derecha
  
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos1++;
    else if (mapa[posf][posc-1] == 2)
      vecinos2++;
            // Si la columna anterior existe [la de la izquierda] se mira si hay un vecino vivo de tipo 1 o 2 en el elemento izquierdo central
  
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos1++;
    else if (mapa[posf][posc+1] == 2)
      vecinos2++;
            // Si existe la columna siguiente [la de derecha] se mira si hay un vecino vivo de tipo 1 o 2 en el elemento derecho central
  
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos1++;
    else if (mapa[posf+1][posc-1] == 2)
      vecinos2++;
            // Si existe la fila siguiente [la de abajo] y la columna anterior [la de la izquierda] mira si hay un vecino vivo y el tipo en el elemento de la diagonal inferior izquierda
  
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos1++;
    else if (mapa[posf+1][posc] == 2)
      vecinos2++;
            // Si existe la fila siguiente [la de abajo] mira si hay un vecino vivo y de que tipo en el elemento inferior central

  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos1++;
    else if(mapa[posf+1][posc+1] == 2)
      vecinos2++;
            // Si existe la fila siguiente [la de abajo] y la columna siguiente [la de la derecha] mira si hay un vecino vivo en el elemento diagonal superior derecho y cual es su tipo
}

void Mapa::ciclo()                             // Esta funcion me hace el paso siguiente del ciclo [operador evolucion]
{
  vector<vector<int> > nueva_conf = mapa;      // Se crea una nueva matriz con los elementos de la vieja
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	       analizarVecinos(f, c);     // Recorre todas las filas y las columnas y va analizando los vecinos para cada elemento
	           
             // Condiciones por si la celula esta muerta
    if(mapa[f][c] == 0)                        // Evalua si la celula esta muerta
            {
	      if(vecinos1 == 3)
		nueva_conf[f][c] = 1;                      // Si la celula esta muerda y el numero de vecinos tipo 1 vivos es igual a 3 cambia la casilla en la matriz nueva a 1 [revive la celular] 
        else if (vecinos2 == 3)
    nueva_conf[f][c] = 2;                      // Si la celula muerta y sus vecinos no fueron 3 de tipo 1 y son 3 de tipo 2 revive como de tipo 2
        else
		nueva_conf[f][c] = 0;                      // En cualquier otro caso la celula permanece muerta
            }
             
             // Condiciones por si la celula esta viva y es de tipo 1
	  if (mapa[f][c] == 1)    // Evalua si la celula es de tipo 1
            {
        if(vecinos1 >= vecinos2 && (vecinos1 == 3 || vecinos1 ==2))
    nueva_conf[f][c] = 1;                      // Si la celula es de tipo 1 y tiene3 o 2 vecinos de su mismo tipo y ademas son mas que los vecinos de tipo 2 la revive como de tipo 1
	      else if(vecinos 2 > vecinos 1 && vecinos2 == 3)
    nueva_conf[f][c] = 2;                      // Si la celula es de tipo 1 y no cumplio v2<=v1 y tiene tres vecinos de tipo dos revive como de tipo 2
        else
		nueva_conf[f][c] = 0;                      // En cualquier otro caso la celula muere
            }

    if (mapa[f][c] == 2)    // Evalua si la celula es ded tipo 2
            {
        if(vecinos1 >= vecinos2 && vecinos1 == 3)  // si es de tipo 2 y tiene mas vecinos de tipo 1 que de tipo 2 y ademas el numero de vecinos tipo 1 es 3 se convierte a tipo 1
    nueva_conf[f][c] = 1;
        else if(vecinos2 > vecinos1 && (vecinos2 == 3 || vecinos2 == 2))  // Si o cumplio lo anterior y tiene 3 o 2 vecinos de tipo dos y sus vecinos de tipo 1 son menos que los de tipo dos se queda en tipo 2
    nueva_conf[f][c] = 2;
        else
    nueva_conf[f][c] = 0;                      //En otros casos la celula muere
            }

      vecinos1 = 0;                            // Como vecinos son variables globales se deben reiniciar al finalizar cada ciclo
      vecinos2 = 0;
      }
    }
  
  mapa = nueva_conf;                           // Me establece la nueva matriz como la vieja
}

int main()
{
  srand(time(NULL));                           // Crea u numero aleatorio, le provee la semilla a srand usando el reloj interno del computador
  Mapa mapa(50, 50);                           // Llama la funcion mapa del a clase Mapa y le da el numero de filas y columnas deseado
  while(1)
    {
      mapa.dibujar();                          // Pinta la matriz
      usleep(100000);                          // usleep establece un tiempo de espera [en microsegundos] para cambiar de contador en el ciclo while
      system("clear");                         // limpia la consola para que la matriz siga saliendo en la misma parte
        mapa.ciclo();                          // Evoluciona ma matriz
    }
}

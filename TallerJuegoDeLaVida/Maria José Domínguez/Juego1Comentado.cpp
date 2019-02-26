#include <iostream> /*incluye la biblioteca que contiene las funciones de entrada y salida de c++*/
#include <cstdlib> /*incluye la biblioteca estandar de propósito general de C*/
#include <vector> /*incluye la clase vector*/
#include <unistd.h> /*incluye la librería que define constantes, tipos y funciones*/

using namespace std; /*esto evita tener que usar siempre el prefijo de la librería estandar a la hora de usar sus funciones*/

class Mapa /*se declara la clase Mapa con miembros públicos "fil" y "col" (enteros), un grid llamado mapa, y funciones "dibujar" y "ciclo" que no entregan nada, una función de contruccion "Mapa" y una función que regresa un entero "analizarVecinos" */
{
public:
  int fil;
  int col;
  int vecinos;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c) /*inicializa la función de contrucción, le da tamaño a al grid, y la llena con números aleatorios entre 0 y 1*/
{
  fil = f;
  col = c;
  mapa.resize(fil);
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col);
    }
  
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%2;
        }
    }
}

void Mapa::dibujar() /*se especifica que hace la función "dibujar", esta comienza a analizar las casillas posicionandose en una fila y recorriendo las columnas en la fila, si en la posición hay un 1 se dibuja el caracter *, si es cero . y cuando termina la fila baja a la siguiente*/
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1)
	    cout << "* ";
	  else
	    cout << ". ";
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos(int posf, int posc) /*se especifica que hace la función "analizarVecinos", lo que hace es contar el número de vecinos dada una posicion, analizando las 8 casillas aledañas una por una y agregando al número de vecinos si en la casilla hay un 1, para regresar el total de vecinos al final*/
{
  vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos++;
  return vecinos;
}

void Mapa::ciclo() /*se especifica que hace la funcion "ciclo", aquí se le asigna una nueva configuración al grid mapa, en la cual ya no hay números aleatorios sino que para cada casilla (recorriendo nuevamente las columnas en las filas) cuenta el número de vecinos, si en la casilla hay un 0 y tiene exactamente 3 vecinos la cambia por un 1, si hay un 1 y tiene 2 o 3 vecinos la deja como 1, sino la cambia a 0*/
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos = analizarVecinos(f, c);
	  if(mapa[f][c] == 0)
            {
	      if(vecinos == 3)
		nueva_conf[f][c] = 1;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1)
            {
	      if(vecinos == 2 || vecinos == 3)
		nueva_conf[f][c] = 1;
	      else
		nueva_conf[f][c] = 0;
            }
        }
    }
  
  mapa = nueva_conf;
}

int main() /*comineza el programa principal*/
{
  srand(time(NULL)); /*hace uso del reloj interno del computador para cambiar el valor inicial para generar una secuencia de numeros enteros semi-aleatorios*/
  Mapa mapa(50, 50); /*le da tamaño al mapa de 50x50 filas y columnas*/
  while(1) /*siempre que dibuje el grid, espere un tiempo, lo borre y dibuje la nueva configuración dada con el ciclo*/
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}

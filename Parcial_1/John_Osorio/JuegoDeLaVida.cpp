//Incluir librerias
#include <iostream>		//Libreria para acciones de entrada/salida de datos.
#include <cstdlib>
#include <vector>		//Libreria para manipular arreglos.
#include <unistd.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace
  std::chrono;
//Declaracion de la clase Mapa.
class
  Mapa
{
//Tipo de acceso de la clase.
public:
  //Atributo fila en la que se encuentra un individuo de la especie.
  int
    fil;
  //Atributo columna en la que se encuentra un individuo de la especie.
  int
    col;
  //Numero de vecinos del individuo.
  int
    vecinos;
  //Matriz de posiciones, la cual representa el mapa.
  vector <
  vector < int >>
    mapa;
  //Implementacion metodo Mapa.
  Mapa (int f, int c);
  //Implementacion metodo dibujar.
  void
  dibujar ();
  //Implementacion metodo analizar vecinos.
  int
  analizarVecinos (int posf, int posc);
  //Implementacion metodo ciclo
  void
  ciclo ();
  //Implementacion metodo vivos
  int
  vivos ();
};

//MC)todo mapa, en el que se inicializa el mapa como matiz de f*c y se llena aleatoriamente.
Mapa::Mapa (int f, int c)
{
  //Numero de filas del mapa
  fil = f;
  //Numero de columnas del mapa
  col = c;
  //Se dimensiona el vector mapa para que tenga f vectores.
  mapa.resize (fil);
  for (int i = 0; i < mapa.size (); i++)
    {
      mapa[i].resize (col);	//Cada vector del mapa se dimensiona para que tenga c elementos.
    }

  for (int f = 0; f < fil; f++)
    {
      for (int c = 0; c < col; c++)
	{
	  mapa[f][c] = rand () % 2;	//Se llena cada posicion del mapa de manera aleatoria con numeros entre 0 y 1.
	}
    }
}

//Metodo para dibujar en consola el mapa
void
Mapa::dibujar ()
{
  //Se recorre por filas
  for (int f = 0; f < fil; f++)
    {
      //Se recorren por columnas
      for (int c = 0; c < col; c++)
	{

	  if (mapa[f][c] == 1)
	    cout << "* ";	//Si en la fila f, columna c, se encuentra la especie 1, entonces esta es representada mediante "*"
	  else
	    cout << ". ";	//En caso contrario, se muestra un "."
	}
      cout << "\n";		//Salto de lC-nea
    }

}

//Funcion que analiza los vecinos de un individuo dada su posicion
int
Mapa::analizarVecinos (int posf, int posc)
{
  //Contador de nC:mero de vecinos
  vecinos = 0;
  //Se analiza cada una de las 8 posiciones adyacentes a la posicion actual
  if (posf - 1 >= 0 and posc - 1 >= 0)
    if (mapa[posf - 1][posc - 1] == 1)	//Si hay un vecino, entonces se aumenta el contador
      vecinos++;
  if (posf - 1 >= 0)
    if (mapa[posf - 1][posc] == 1)
      vecinos++;
  if (posf - 1 >= 0 and posc + 1 <= col - 1)
    if (mapa[posf - 1][posc + 1] == 1)
      vecinos++;
  if (posc - 1 >= 0)
    if (mapa[posf][posc - 1] == 1)
      vecinos++;
  if (posc + 1 <= col - 1)
    if (mapa[posf][posc + 1] == 1)
      vecinos++;
  if (posf + 1 <= fil - 1 and posc - 1 >= 0)
    if (mapa[posf + 1][posc - 1] == 1)
      vecinos++;
  if (posf + 1 <= fil - 1)
    if (mapa[posf + 1][posc] == 1)
      vecinos++;
  if (posf + 1 <= fil - 1 and posc + 1 <= col - 1)
    if (mapa[posf + 1][posc + 1] == 1)
      vecinos++;
  return vecinos;		//Se devuelve la cantidad de vecinos.
}

//Metodo en el que se analiza cada posicion del mapa para contar el numero de vecinos y aplicar las reglas del juego de la vida
void
Mapa::ciclo ()
{

  //Mapa actualizado una vez aplicadas las reglas del juego
  vector < vector < int >>nueva_conf = mapa;

  //Se recorre por filas el mapa 
  for (int f = 0; f < fil; f++)
    {
      //Se recorre por columnas el mapa
      for (int c = 0; c < col; c++)
	{
	  //Se encuentra el numero de vecinos para el individuo en la fila f y la columna c
	  int n_vecinos = analizarVecinos (f, c);
	  if (mapa[f][c] == 0)	//Si en la posicion no hay ningun individuo
	    {
	      if (vecinos == 3)	//Y el numero de vecinos es 3
		nueva_conf[f][c] = 1;	//Entonces esta posicion es poblada con un individuo
	      else
		nueva_conf[f][c] = 0;	//Sino, se deja vacio
	    }
	  if (mapa[f][c] == 1)	//Si en la posicion hay un individuo,
	    {
	      if (vecinos == 2 || vecinos == 3)	//Y tiene 2 o 3 vecinos
		nueva_conf[f][c] = 1;	//Entonces sobrevive
	      else
		nueva_conf[f][c] = 0;	//Sino, muere
	    }
	}
    }

  mapa = nueva_conf;		//Actualiza la matriz mapa
}

//Metodo para encontrar el numero de individuos vivos en el mapa
int
Mapa::vivos ()
{
  //Contador de individuos vivos
  int c = 0;
  for (int i = 0; i < fil; i++)
    {
      for (int j = 0; j < col; j++)
	{
	  //Se mira si en la posicion del mapa hay un individuo vivo
	  if (mapa[i][j] == 1)
	    c++;
	}
    }
  return c;
}


//Metodo principal

int
JuegoDeLaVida (int n)
{
  srand (time (NULL));		////FunciC3n para inicializar el generator de numeros aleatorios.
  Mapa mapa (n, n);		//Instancia de la clase mapa, con 50 filas y 50 columnas
  //Con esta variable se analiza el numero de veces consecutivas que el mapa tiene el mismo numero de celulas vivas
  int estable = 0;
  vector <int> vivos = {0, 0, 0, 0};
  
  //Para medir el tiempo de ejecucion
  auto start = high_resolution_clock::now ();
  auto stop = high_resolution_clock::now ();

  while (1)			//Se repite de manera indefinida
    {
      mapa.dibujar ();		//Se dibuja el mapa en pantalla
      usleep (100000);		//Establece un tiempo de espera
      system ("clear");		//Limpia la consola
      mapa.ciclo ();		//Se recorre el Mapa
      //Se analiza si el numero de vivos en el nuevo mapa es el mismo que en el anterior
      if (mapa.vivos () == vivos[1] or mapa.vivos() == vivos[0] or mapa.vivos() == vivos[2] or mapa.vivos() == vivos[3])
	{
	  if (estable == 0)
	    stop = high_resolution_clock::now ();
	  estable++;
	}
      else
	{
	  estable = 0;
	}
      if (estable > 5)
	break;
      vivos[0] = vivos[1];
      vivos[1] = vivos[2];
      vivos[2] = vivos[3];
      vivos[3] = mapa.vivos ();
}
  mapa.dibujar ();
  auto duration = duration_cast < milliseconds > (stop - start);

  cout << "Tiempo de estabilizacion para n = " << n << ": "
    << duration.count () << " milisegundos" << endl;
  return duration.count ();
}

//Funcion para calcular los tiempos de estabilizacion para un n
void
estabilizacion (int n)
{

  int N = 20;
  vector < int > vals;
  //Los tiempos se almacenan en un archivo de texto
  ofstream myfile;
  myfile.open ("data.dat");  
  
  vals.resize (N);
  myfile << n << " "; 
  for (int j = 0; j < N; j++)
    {
      
      myfile << JuegoDeLaVida (n) << " "; 
      
    }
   myfile << "\n";
   myfile.close();
}

int
main ()
{
  cout << "Ingrese la dimension de la matriz ";
  int n = 0;
  cin >> n;
  JuegoDeLaVida (n);
  //estabilizacion(n);
}



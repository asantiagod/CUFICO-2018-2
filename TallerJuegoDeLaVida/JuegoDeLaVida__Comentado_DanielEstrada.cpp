// Librerias estandar de c++
#include <iostream> // libreria estandar de entradas y salidad
#include <cstdlib> // gestion de memeoria y control de procesos
#include <vector> // provee la plantilla clase contenedora std::vector
#include <unistd.h> // contiene la funcion usleep 

using namespace std; // quita es prefijo std:: en el uso de las funciones que trae esta libreria 

class Mapa
{ // Atributos publicos de la clase MAPA
public:
  int fil;
  int col;
  int vecinos;
  vector<vector<int> > mapa; // mapa es una matriz 
  
  // Prototipos de los metodos de la clase Mapa 
  Mapa(int f, int c); // constructor de la clase
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

// definicion del metodo Mapa de la clase Mapa
Mapa::Mapa(int f, int c)
{
  fil = f;
  col = c;
  mapa.resize(fil); // con rezise se redefine el tampaño del mapa
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col); // en cada entrada de mapa, añade un arreglo de dimension col
    }
  // con el anterior for se establecio mapa como una matriz de tamaño (fil,col), el siguiente for es para asignarle valores a cada entrada de mapa
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%2;
        }
    }
}

void Mapa::dibujar()
// este metodo inicializa el mapa añadiendo "celulas" vivas o muertas segun la entrada que se le asigno con rand
// si la entrada es 1, la celula esta viva entonces se dibuja un "*". si la entrada es 0, la celula esta muerta y se
// dibuja un "."
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

// este metodo analizara los entornos de las celulas y contara cuantos vecinos hay vivos 
int Mapa::analizarVecinos(int posf, int posc)
{
  vecinos = 0; // contador de vecinos 
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

void Mapa::ciclo()
// Esta rutina hace una copia de la matriz para ir modificando los valores de las entradas segun las reglas del juego de la vida
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
  
  mapa = nueva_conf; // se redefine el mapa de tal manera que los cambio ocurridos en una iteracion queden registrados
}

int main()
{
  srand(time(NULL));// con esta lista usa como semilla de numeros aleatroios la hora en la que se ejecuta el codigo
  Mapa mapa(50, 50);
  while(1)
    {
      mapa.dibujar();
      usleep(100000); // esta linea hace un delay 
      system("clear");
        mapa.ciclo(); // evoluciona el mapa en cada iteracion
    }
}

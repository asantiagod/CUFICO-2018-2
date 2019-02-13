#include <iostream> //Para imprimir datos por consola
#include <cstdlib>
#include <vector>	//Manejo de arreglos de objetos sde tamaño no definido
#include <unistd.h> //Funciones propias para los sistemas operativos tipo POXIS

using namespace std; //Usar el namespace para hacer uso del 'scope' estándar

class Mapa //Definición de la clase Mapa
{
public:
  int fil; // Núrero de filas
  int col; // Número de columnas
  int vecinos; //Número de vecinos la última célula analizada
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);	//Constructor de la clase
  void dibujar();  		//"Dibujar" en consola el mapa
  int analizarVecinos(int posf, int posc); //Analiza los vecinos de la célula que está en la posición (posf,posc)
  void ciclo();
};

/*
 * Implementación del constructor
 * f Número de filas que tendrá el mapa
 * c Número de columnas que tendrá el mapa	
 */
Mapa::Mapa(int f, int c)
{
  fil = f;
  col = c;
  mapa.resize(fil);//Número de elementos del mapa igual al número de filas

  /* Loop para que cada "fila" del mapa contenga col "columnas",
   * es decir, que el mapa queda de orden fil x col
   */
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col); //Cada fila del mapa contendrá  col "columnas"
    }
  
  /* Llenar el mapa con 0s o 1s de forma aleatoria*/
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%2; //asignar de forma aleatoria un 0 o un 1
        }
    }
}

/* Implentación del método 'dibujar' */
void Mapa::dibujar()
{
  for(int f=0; f<fil; f++) //Recorer filas
    {
      for(int c=0; c<col; c++) //recorrer columnas
        {
	  if(mapa[f][c] == 1)
	    cout << "* ";	//Imprimir celula viva
	  else
	    cout << ". ";	//Imprimir celula muerta
        }
      cout << "\n";		//Salto de linea
    }
}

/* Implementación del método "analizarVecinos"
 * posf Fila de la célula a analizar
 * posc Columna de la célula a analizar
 */
int Mapa::analizarVecinos(int posf, int posc)
{
	// Esquema de los vecinos 
	//  __ __ __
	// |v1|v2|v3|
	// |v4|  |v5|
	// |v6|v7|v8|
	//

  vecinos = 0; //Inicializar el número de vecinos de la célula
  
  /* Todos los "if" antes de analizar el valor de los vecinos, 
   * se usan para garantizar que, si el punto (posf, posc) se 
   * encuetra en un "borde" del mapa, no analice un vecino inexistente*/ 

  /* Analizar vecino v1*/
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;

  /* Analizar vecino v4*/
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos++;

  /* Analizar vecino v6*/
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;

  /* Analizar vecino v2*/
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos++;

  /* Analizar vecino v7*/
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos++;

  /* Analizar vecino v3*/
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos++;

  /* Analizar vecino v5*/
  if(posf+1 <= fil-1)  	
    if(mapa[posf+1][posc] == 1)
      vecinos++;

  /* Analizar vecino v8*/
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos++;

  return vecinos;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa; //Crea una copia auxiliar del mapa
  
  /*Recorer filas*/
  for (int f=0; f<fil; f++)
    {
      /*recorrer columnas*/
      for(int c=0; c<col; c++)
        {
	  int n_vecinos = analizarVecinos(f, c); // Analizar los vecinos de la célula en (f, c)

	  /* Aplicar las reglas del "Juego de la vida" */
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
  
  mapa = nueva_conf; //Copiar el mapa auxiliar en el mapa
}

/* Programa */
int main()
{
  srand(time(NULL)); //Inicializar semilla para los números aleatorios
  Mapa mapa(50, 50); //Crear mapa de 50x50

  /*loop infinito*/
  while(1)
    {
      mapa.dibujar(); //Dibujar el mapa actual
      usleep(100000); //Esperar 0.1 segundos
      system("clear"); //Limpiar la terminal
        mapa.ciclo();  //Modificar el mapa
    }
}

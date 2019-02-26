#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

class Mapa
{
public: //Las clases tienen dos tipos de miembros: publicos y privados
  int fil;
  int col;
  int vecinos1, vecinos2;
  int valor;
  vector<vector<int> > mapa; //Crea una matriz pero no le da dimensiones
  
  Mapa(int f, int c); //Ejecuta la funcion Mapa perteneciente a la clase Mapa, ya que tienen el mismo nombre
  void dibujar(); //Inicializa las funciones
  vector<int> analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c) //Funcion dentro de la clase Mapa que inicializa el mapa del juego
{
  fil = f;
  col = c;
  mapa.resize(fil); //Redimensiona la matriz en las filas
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col); //Ahora redimenciona las columnas por cada fila
    }
  
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%3; //A cada punto del mapa asigna un valor entre 0 y 2 aleatorio
        }
    }
}

void Mapa::dibujar() //Funcion dentro de la clase Mapa que lo dibuja
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1) //Si el valor del punto fc es 1, entonces asignar una estrella
	    cout << "* ";
	  else if(mapa[f][c] == 2) //Si el valor del punto fc es 2, entonces asignar un circulo
	    cout << "o ";
	  else
	    cout << ". "; //De lo contrario poner un punto
	}
      cout << "\n";
    }
}

vector<int> Mapa::analizarVecinos(int posf, int posc) //Cuenta el numero de vecinos dada una posicion
{
  vecinos1 = 0; //Contamos desde cero el numero de vecinos
  vecinos2 = 0;
  if(posf-1 >= 0 and posc-1 >= 0){ //Si no esta en la esquina inferior izquierda
    if(mapa[posf-1][posc-1] == 1) //contar si tiene un vecino (un asterisco)
      vecinos1++;
    else if(mapa[posf-1][posc-1] == 2)
      vecinos2++;}
  if(posf-1 >= 0){ //Si no esta en la pared izquierda
    if(mapa[posf-1][posc] == 1)
      vecinos1++;
    if(mapa[posf-1][posc] == 2)
      vecinos2++;}
  if(posf-1 >= 0 and posc+1 <= col-1){ //En general si no esta en una frontera
    if(mapa[posf-1][posc+1] == 1)
      vecinos1++;
    if(mapa[posf-1][posc+1] == 2)
      vecinos2++;}
  if(posc-1 >= 0){
    if(mapa[posf][posc-1] == 1)
      vecinos1++;
    if(mapa[posf][posc-1] == 2)
      vecinos2++;}
  if(posc+1 <= col-1){
    if(mapa[posf][posc+1] == 1)
      vecinos1++;
    if(mapa[posf][posc+1] == 2)
      vecinos2++;}
  if(posf+1 <= fil-1 and posc-1 >= 0){
    if(mapa[posf+1][posc-1] == 1)
      vecinos1++;
    if(mapa[posf+1][posc-1] == 2)
      vecinos2++;}
  if(posf+1 <= fil-1){
    if(mapa[posf+1][posc] == 1)
      vecinos1++;
    if(mapa[posf+1][posc] == 2)
      vecinos2++;}
  if(posf+1 <= fil-1 and posc+1 <= col-1){
    if(mapa[posf+1][posc+1] == 1)
      vecinos1++;
    if(mapa[posf+1][posc+1] == 2)
      vecinos2++;}
  return {vecinos1, vecinos2};
}

void Mapa::ciclo() //Funcion que hace que el mapa avance
{
  vector<vector<int> > nueva_conf = mapa; //Se hace una copia del mapa que modificaremos en orden
  for (int f=0; f<fil; f++)               //esto se hace para no mezclar informacion vieja del mapa con nueva
    {
      for(int c=0; c<col; c++)
        {
	  int vecinos1 = analizarVecinos(f, c)[0];
	  int vecinos2 = analizarVecinos(f, c)[1]; //Cuantos vecinos tiene la casilla fc
	  if(mapa[f][c] == 0) //Si en la casilla fc no hay una entidad
            {
	      if(vecinos1 >= vecinos2 && vecinos1 == 3) //Si tiene mas de 3 vecinos, entonces se vuelve una entidad
		nueva_conf[f][c] = 1;
	      else if(vecinos2 > vecinos1 && vecinos2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1) //Si en la casilla fc si hay una entidad
            {
	      if(vecinos1 >= vecinos2 && (vecinos1 == 3 || vecinos1 == 2)) //
		nueva_conf[f][c] = 1;
	      else if(vecinos2 > vecinos1 && vecinos2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 2)
	    {
	      if(vecinos1 >= vecinos2 && vecinos1 == 3)
		nueva_conf[f][c] = 1;
	      else if(vecinos2 > vecinos1 && (vecinos2 == 2 || vecinos2 == 3))
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
	    }
        }
    }
  
  mapa = nueva_conf; //Ahora, reasignamos el valor del mapa
}

int main()
{
  srand(time(NULL)); // Inicializa el generador de numeros aleatorios usando el tiempo como semilla
  Mapa mapa(50, 50); //Llama a la variable mapa de la clase Mapa
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}

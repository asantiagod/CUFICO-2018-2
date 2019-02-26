#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

class Mapa
{
public:
  int fil;			//longitud de las filas de la matriz
  int col;			//longitud de las columnas de la matriz
  int vecinos_1;		//cantidad de vecinos de la especie 1
  int vecinos_2;		//cantidad de vecinos de la especie 2
  vector<vector<int> > mapa;	//matriz sin dimensiones definidas
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos_1(int posf, int posc);
  int analizarVecinos_2(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)	//funcion que genera la matriz inicial de tamaño f*c
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
	  mapa[f][c] = rand()%3;//llena el mapa con numeros aleatorios entre el 0 y el 2
        }
    }
}

void Mapa::dibujar()			//funcion que genera el aspecto grafico del juego teniendo en cuenta los datos de la matriz
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1)		//asigna a la especie 1 el simbolo *
	    cout << "* ";
	  else if(mapa[f][c] == 2)	//asigna a la especie 2 el simbolo +
	    cout << "+ ";
	  else
	    cout << ". ";		//asigna a las casillas "muertas" el simbolo .
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos_1(int posf, int posc)	//funcion que cuenta la cantidad de vecinos de la especie 1 que tiene cada casilla, teniendo en 						cuenta la posicion de la casilla
{
  vecinos_1 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos_1++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos_1++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos_1++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos_1++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos_1++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos_1++;
  return vecinos_1;
}

int Mapa::analizarVecinos_2(int posf, int posc)	//funcion que cuenta la cantidad de vecinos de la especie 2 que tiene cada casilla, teniendo en 						cuenta la posicion de la casilla
{
  vecinos_2 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 2)
      vecinos_2++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 2)
      vecinos_2++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 2)
      vecinos_2++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 2)
      vecinos_2++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 2)
      vecinos_2++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 2)
      vecinos_2++;
  return vecinos_2;
}

void Mapa::ciclo()				//funcion que calcula la configuracion del juego para el siguiente turno
{
  vector<vector<int> > nueva_conf = mapa;	//genera la matriz del proximo turno con el mismo tamaño que la matriz del turno actual
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos_1 = analizarVecinos_1(f, c);
          int n_vecinos_2 = analizarVecinos_2(f, c);
	  if(mapa[f][c] == 0)			//si la casilla esta "muerta" revisa que estado tendra en el siguiente turno
            {
	      if(vecinos_1 >= vecinos_2 and vecinos_1 == 3)
		nueva_conf[f][c] = 1;
	      else if(vecinos_1 < vecinos_2 and vecinos_2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1)			//si la casilla es de la especie 1 revisa que estado tendra en el siguiente turno
            {
	      if(vecinos_1 >= vecinos_2 and (vecinos_1 == 2 || vecinos_1 == 3))
		nueva_conf[f][c] = 1;
              else if(vecinos_1 < vecinos_2 and vecinos_2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 2)			//si la casilla es de la especie 2 revisa que estado tendra en el siguiente turno
            {
	      if(vecinos_1 >= vecinos_2 and vecinos_1 == 3)
		nueva_conf[f][c] = 1;
              else if(vecinos_1 < vecinos_2 and (vecinos_2 == 2 || vecinos_2 == 3))
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
        }
    }
  
  mapa = nueva_conf;	//cambia en memoria la matriz actual por la del siguiente turno
}

int main()	//codigo principal
{
  srand(time(NULL));
  Mapa mapa(50, 50);
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}

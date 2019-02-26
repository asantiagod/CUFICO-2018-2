#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <chrono>

using namespace std;

class Mapa
{
public:
  int fil;
  int col;
  int vecinos;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(vector<vector<int> > dummymap, int posf, int posc);
  int ciclo();
};

Mapa::Mapa(int f, int c)		//Creacion de la matriz inicial aleatoria llena de 0's y 1's que generara el mapa
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

void Mapa::dibujar()			//Creacion del mapa visual
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

int Mapa::analizarVecinos(vector<vector<int> > dummymap, int posf, int posc)	//Conteo sobre cada celda de la cantidad de vecinos con valor 											  "1" 
{
  vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(dummymap[posf-1][posc-1] == 1)
      vecinos++;
  if(posf-1 >= 0)
    if(dummymap[posf-1][posc] == 1)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(dummymap[posf-1][posc+1] == 1)
      vecinos++;
  if(posc-1 >= 0)
    if(dummymap[posf][posc-1] == 1)
      vecinos++;
  if(posc+1 <= col-1)
    if(dummymap[posf][posc+1] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(dummymap[posf+1][posc-1] == 1)
      vecinos++;
  if(posf+1 <= fil-1)
    if(dummymap[posf+1][posc] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(dummymap[posf+1][posc+1] == 1)
      vecinos++;
  return vecinos;
}

int Mapa::ciclo()
{
  int condicion = 1;				//Condicion de estabilidad
  vector<vector<int> > nueva_conf = mapa;	//Nueva configuracion de la matriz
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  analizarVecinos(mapa, f, c);
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

  for(int f=0;f<fil;f++)			//Analisis de la condicion de estabilidad sobre cada celda
    {
      for(int c=0;c<col;c++)
	{
	  if((mapa[f][c] == 1) && (nueva_conf[f][c] == 1))
	    {
	      int n1 = analizarVecinos(mapa, f, c);
	      int n2 = analizarVecinos(nueva_conf, f, c);
	      if(n1 == n2)
		condicion *= 1;
	      else
		condicion *= 0;
	    }
	}
    }
  
  mapa = nueva_conf;
  return condicion;
}

int main()
{
  int n;
  int bkcondition;
  srand(time(NULL));
  cout << "Por favor ingrese un numero entero para definir las dimensiones del mapa\n";
  cin >> n;
  auto start = chrono::high_resolution_clock::now();
  Mapa mapa(n, n);
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
      bkcondition = mapa.ciclo();
      if(bkcondition)
	{
	  mapa.dibujar();
	  break;
	}
    }
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = finish - start;
  cout << "El tiempo que tardo el sistema para estabilizarse es: "<< elapsed.count() << "s\n";
  return 0;
}

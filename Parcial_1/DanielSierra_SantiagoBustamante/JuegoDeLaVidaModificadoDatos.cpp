#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <fstream>

//Este es el mismo codigo que el JuegoDeLaVidaModificado solo que con un ciclo para realizar varios conteos de tiempo para la misma dimasion n

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

Mapa::Mapa(int f, int c)
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

void Mapa::dibujar()
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

int Mapa::analizarVecinos(vector<vector<int> > dummymap, int posf, int posc)
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
  int condicion = 1;
  vector<vector<int> > nueva_conf = mapa;
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

  for(int f=0;f<fil;f++)
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
  ofstream datafile;
  string filename = "datos_" + to_string(n) + ".dat";
  datafile.open(filename.c_str(), fstream::trunc);
  for(int i = 0; i<30; i++)
    {
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
      datafile << elapsed.count() << "\n";
    }
  datafile.close();
  return 0;
}

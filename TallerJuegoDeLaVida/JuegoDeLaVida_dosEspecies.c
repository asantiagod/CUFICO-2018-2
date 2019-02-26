#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

class Mapa
{
public:
  int fil;
  int col;
  int n_vecinos_1;
  int n_vecinos_2;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc, int type);
  void ciclo();
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
	  mapa[f][c] = rand()%3;
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
	  else if(mapa[f][c] == 2)
	    cout << "# ";
    else
      cout<< ". ";
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos(int posf, int posc, int type)
{
  int vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == type)
      vecinos++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == type)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == type)
      vecinos++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == type)
      vecinos++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == type)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == type)
      vecinos++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == type)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == type)
      vecinos++;
  return vecinos;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
          n_vecinos_1 = analizarVecinos(f, c, 1);
          n_vecinos_2 = analizarVecinos(f, c, 2);

          if(mapa[f][c] == 0)
          {
            if(n_vecinos_1 == 3)
              nueva_conf[f][c] = 1;
            else if(n_vecinos_2 == 3)
              nueva_conf[f][c] = 2;
            else
              nueva_conf[f][c] = 0;
          }
          if (mapa[f][c] == 1)
          {
            if(n_vecinos_1>=n_vecinos_2 && (n_vecinos_1 == 2 || n_vecinos_1 == 3))
              nueva_conf[f][c] = 1;
            else if(n_vecinos_2>n_vecinos_1 && n_vecinos_2 == 3)
              nueva_conf[f][c] == 2;
            else 
              nueva_conf[f][c] == 0;
          } 
          
          if (mapa[f][c] == 2)
          {
            if(n_vecinos_1 >= n_vecinos_2 && n_vecinos_1 == 3)
              nueva_conf[f][c] = 1;
            else if(n_vecinos_2 > n_vecinos_1 && (n_vecinos_2 == 2 || n_vecinos_2 == 3)){
                nueva_conf[f][c] = 2;
            }
            else
              nueva_conf[f][c] = 0;
          }
        }
    }
  
  mapa = nueva_conf;
}

int main()
{
  srand(time(NULL));
  Mapa mapa(50, 50);
  while(int i=0)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
      mapa.ciclo();
      i = 1

    }
}

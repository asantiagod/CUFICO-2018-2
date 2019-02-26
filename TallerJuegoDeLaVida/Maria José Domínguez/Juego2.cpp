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
  int vecinos1;
  int vecinos2;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos1(int posf, int posc);
  int analizarVecinos2(int posf, int posc);
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
	  else if (mapa[f][c] == 2)
	    cout << "+ ";
	  else
	    cout << ". ";
        }
      cout << "\n";
    }
}
int Mapa::analizarVecinos1(int posf, int posc)
{
  vecinos1 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos1++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos1++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos1++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos1++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos1++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos1++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos1++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos1++;
  return vecinos1;
}

int Mapa::analizarVecinos2(int posf, int posc)
{
  vecinos2 = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 2)
      vecinos2++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 2)
      vecinos2++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 2)
      vecinos2++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 2)
      vecinos2++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 2)
      vecinos2++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 2)
      vecinos2++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 2)
      vecinos2++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 2)
      vecinos2++;
  return vecinos2;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos1 = analizarVecinos1(f, c);
	  int n_vecinos2 = analizarVecinos2(f, c);
	  if(mapa[f][c] == 0)
            {
	      if(vecinos1 == 3 && vecinos1 >= vecinos2)
		nueva_conf[f][c] = 1;
		  else if(vecinos2 ==3 && vecinos2 > vecinos1)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
	  if (mapa[f][c] == 1)
            {
	      if(vecinos1 == 2 || vecinos1 == 3 && vecinos1 >= vecinos2)
		nueva_conf[f][c] = 1;
		  else if(vecinos1 == 2 || vecinos1 == 3 && vecinos2 > vecinos1)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0;
            }
      if (mapa[f][c] == 2)
            {
	      if(vecinos2 == 2 || vecinos2 == 3 && vecinos2 > vecinos1)
		nueva_conf[f][c] = 2;
		  else if(vecinos2 == 2 || vecinos2 == 3 && vecinos1 >= vecinos2)
		nueva_conf[f][c] = 1;
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
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}

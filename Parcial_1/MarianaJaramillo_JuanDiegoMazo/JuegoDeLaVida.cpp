#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include<ctime>
#include<fstream>

using namespace std;

int Vivos;

class Mapa
{
public:
  int fil;
  int col;
  int vecinos;
  int Vivos;
  
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
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

int Mapa::analizarVecinos(int posf, int posc)
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

int Mapa::ciclo()
{  
  vector<vector<int> > nueva_conf = mapa;
  Vivos = 0;
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
          Vivos ++;
	      if(vecinos == 2 || vecinos == 3)
		nueva_conf[f][c] = 1;
	      else
		nueva_conf[f][c] = 0;
            }
        }
    } 
  mapa = nueva_conf;
  return Vivos;
}

int main()
{   

  vector<int> VIVOS;
  VIVOS.resize(50);
  printf("Ingrese el orden de la matriz n: ");
  int n, N;
  double time_req;
  char Nombre[15]; 
  scanf ("%d", &n);
  N = sprintf(Nombre, "Dato_%d.txt", n);
  ofstream myfile;
  myfile.open(Nombre);
  
  for (int j = 0; j<4; j++)
    {
  
   
  srand(time(NULL));
  Mapa mapa(n, n);
  clock_t time_req;
  
  time_req = clock();
  int i = 12;
  while(1)
    {
      
      mapa.dibujar();
      usleep(100000);
      system("clear");
        VIVOS[i] = mapa.ciclo();
        if (VIVOS[i] == VIVOS[i-1] && VIVOS[i]==VIVOS[i-2] && VIVOS[i]==VIVOS[i-3] && VIVOS[i]==VIVOS[i-4] && VIVOS[i]==VIVOS[i-5] && VIVOS[i]==VIVOS[i-6]
        && VIVOS[i]==VIVOS[i-7] && VIVOS[i] == VIVOS[i-8])
           break;
        else if (VIVOS[i] == VIVOS[i-2] && VIVOS[i]==VIVOS[i-4] && VIVOS[i] == VIVOS[i-6] && VIVOS[i] == VIVOS[i-8])
           break;
        else if (VIVOS[i] == VIVOS[i-3] && VIVOS[i]==VIVOS[i-6] && VIVOS[i] == VIVOS[i-9] && VIVOS[i] == VIVOS[i-12])
            break;
        i++;                     
    }
 /*   
  for (int j = 0; j < VIVOS.size(); j++)
  {
  printf("%d \t", VIVOS[j]);
    }
  printf("\n"); */
  VIVOS.clear();
  VIVOS.resize(50);
    
  time_req = clock() - time_req; 
  
  myfile  << ("%f" , time_req ) << endl ;      
  
    }
    myfile.close();
}

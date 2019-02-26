#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <chrono> 
using namespace std::chrono; 
using namespace std;

int n;
int s;

class Mapa
{
public:
  int fil;
  int col;
  int vecinos;

  int Contador;
  vector<vector<int> > mapa;
  vector<vector<int> > M;
  vector<vector<int> > N;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc,vector<vector<int> > MAPA);
  int ContadorUnos(int posf,int posc,vector<vector<int> > mapa);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
	
  
  fil = n;
  col = n;
  f=n;
  c=n;
 
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

int Mapa::analizarVecinos(int posf, int posc, vector<vector<int> > mapa)
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

int Mapa::ContadorUnos(int posf, int posc, vector<vector<int> > MAPA)
{
  Contador=0;

  for (int posf = 0; posf<fil; posf++)
     {
      for(int posc = 0; posc<col; posc++)
         if (MAPA[posf][posc] == 1)
           {
            Contador++;
           }
     }
  return Contador;

}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
     
      for(int c=0; c<col; c++)
        {
	 
	  int n_vecinos = analizarVecinos(f, c, mapa);
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
  

  if(ContadorUnos(fil, col, mapa) == ContadorUnos(fil, col, nueva_conf)) 
	{
	 int i=0;
         int j=0;
         for (int f=0; f<fil; f++)
             {
              for(int c=0; c<col; c++)
                 {
                
		  if (mapa[f][c]==1 && nueva_conf[f][c]==1)
		    {
		     j++;
		     if (analizarVecinos(f, c, nueva_conf) == analizarVecinos(f, c, mapa))
		       {
                        i++;
                       }
                    }
                 }
              }
         if(i==j)
           {
           s=1;
           return;
           }
        }
   

  mapa = nueva_conf;
}

int main()
{
  cout<<"Ingrese el tamano de la matriz que desea: ";
  cin>> n;
  ofstream myfile;
  string filename = "TiemposDeEstabilizacion"+ to_string(n) + ".dat";
  myfile.open(filename.c_str(), fstream::trunc);
  
for(int i=0; i<30;i++)
    {
      
      srand(time(NULL));
      Mapa mapa(n, n);

      auto start = std::chrono::high_resolution_clock::now();

      while(1)

        {
  
         //mapa.dibujar();
         //usleep(100000);
         //system("clear");
         mapa.ciclo();
      
         if (s==1)
           {
            s=0;
	    break; 
           }
         }
         
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = finish - start;
      std::cout << "Elapsed time: " << elapsed.count() << " s\n"; 
      myfile << elapsed.count() << "\n";
      
      }
  myfile.close();
  return 0;
}

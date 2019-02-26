#include <iostream> // Input/output library
#include <cstdlib> // Standard library
#include <vector> // Vector Class
#include <unistd.h> // Provides access to the programming interface

using namespace std; // Avoids the use of 'std' throughout the code

class Mapa 
{
public: // Public members of the class 'Mapa'
  int fil;
  int col;
  int vecinos;
  vector<vector<int> > mapa; // Builds a matrix of vectors named 'mapa'
  
  Mapa(int f, int c); // Class builder
  
  // Prototypes
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c) // Defines function 'Mapa'
{
  fil = f;
  col = c;
  mapa.resize(fil); // Resizes the matrix 'mapa' with the number of rows
  
  // Resizes each row with the number of columns
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col);
    }
    
  // Fills the matrix with random numbers
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%2;
        }
    }
}

void Mapa::dibujar() // Defines function 'dibujar'
{
  for(int f=0; f<fil; f++)
    {
      // Iterates trhough matrix, if the cell is alive the output signal is '*', if not, '.'
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

int Mapa::analizarVecinos(int posf, int posc) // Defines function 'analizarVecinos'
// Counts the neighbors alive and save that number in 'vecinos'
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

void Mapa::ciclo() // Defines function 'ciclo'
{
  vector<vector<int> > nueva_conf = mapa; // Replaces 'mapa' for a new configuration following the rules of the game
  
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
  
  mapa = nueva_conf; // Saves the new configuration in 'mapa'
}

int main() 
{
  srand(time(NULL)); // Uses a different seed for the inicialization of the random numbers
  Mapa mapa(50, 50);
  while(1)
    {
      mapa.dibujar();
      usleep(100000);
      system("clear");
        mapa.ciclo();
    }
}

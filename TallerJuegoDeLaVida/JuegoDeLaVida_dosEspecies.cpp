/*
  Daniel Estrada Acevedo
  c.c 1020482401
  12 de febrero de 2019 
*/

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
  // a diferencia del juego de la vida simple, aca se define dos tipos de vecinos 
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
    // se modifica los posibles valores inciales que se le dan cambiando %2 por %3
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
    // se añade el simbolo # para designar la segunda especie
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
  // A este metodo se le añade un parametro para contar el numero de vecinos de un cierto tipo
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
          int n_vecinos_1 = analizarVecinos(f, c, 1); // numero de vecinos de la posicion f,c de la especie 1
          int n_vecinos_2 = analizarVecinos(f, c, 2); // numero de vecinos de la posicion f,c de la especie 2

          // Esta condicion determina cuando nace una celda que estaba en cero
          if(mapa[f][c] == 0){
            if(n_vecinos_1 == 3)
              nueva_conf[f][c] = 1;
            else if(n_vecinos_2 == 3)
              nueva_conf[f][c] = 2;
            else
              nueva_conf[f][c] = 0; 
          }
          // en una celda que contiene una celula de la especie 1 prevalencen las reglas del juego de la vida ordinario
          if (mapa[f][c] == 1){
            if(n_vecinos_1 >= n_vecinos_2 && (n_vecinos_1 == 2 || n_vecinos_1 == 3))
              nueva_conf[f][c] = 1; 
            // En caso de haber mas vecinos de la especie dos, este solo cambiara a la especie 2 si el numero de vecinos de esta especie es 3
            else if(n_vecinos_2 > n_vecinos_1 && n_vecinos_2 == 3)
                  nueva_conf[f][c] = 2;
            else
              nueva_conf[f][c] = 0;  
          }
          if (mapa[f][c] == 2){
            // se vuelve a dar prevalencia a las reglas de la especie 1, si se cumple este caso la celula cambiara a ser del tipo 1
            if (n_vecinos_1 >= n_vecinos_2 && n_vecinos_1 == 3)
              nueva_conf[f][c] = 1;
            else if (n_vecinos_2 > n_vecinos_1 && (n_vecinos_2 == 2 || n_vecinos_2 == 3))
              nueva_conf[f][c] = 2;
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

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
  int vecinosE1;
  int vecinosE2;
  vector<vector<int> > mapa; //Matriz sin ninguna dimension
  
  Mapa(int f, int c);
  void dibujar();
  vector<int> analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
  fil = f;
  col = c;
  mapa.resize(fil);
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col); //Cambia el tamaño de acuerdo al valor que le ingrese
    }
  
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%3; //% saca el modulo de 3 de un numero entero
        }
    }
}

void Mapa::dibujar()
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 1) //Criterio de la especie 1
	    cout << "* ";
	  else if(mapa[f][c] == 2) //Criterio de la especie 2
	    cout << "o ";
	  else
	    cout << ". ";
        }
      cout << "\n";
    }
}

vector<int> Mapa::analizarVecinos(int posf, int posc)
{
  vecinosE1 = 0; //Valor inicial de los vecinos de una casillas
  vecinosE2 = 0;

//Analizar posición 1
  if(posf-1 >= 0 and posc-1 >= 0)
	{
    if(mapa[posf-1][posc-1] == 1)
      vecinosE1++;
    else if(mapa[posf-1][posc-1] == 2) 
      vecinosE2++;
	}

//Analizar posición 2
  if(posf-1 >= 0)
	{
    if(mapa[posf-1][posc] == 1)
      vecinosE1++;
    else if(mapa[posf-1][posc] == 2)
      vecinosE2++;
	}

//Analizar posición 3
  if(posf-1 >= 0 and posc+1 <= col-1)
	{
    if(mapa[posf-1][posc+1] == 1)
      vecinosE1++;
    else if(mapa[posf-1][posc+1] == 2)
      vecinosE2++;
	}

//Analizar posición 4
  if(posc-1 >= 0)
	{
    if(mapa[posf][posc-1] == 1)
      vecinosE1++;
    else if(mapa[posf][posc-1] == 2)
      vecinosE2++;
 	}

//Analizar posición 5
  if(posc+1 <= col-1)
	{
    if(mapa[posf][posc+1] == 1)
      vecinosE1++;
    else if(mapa[posf][posc+1] == 2)
      vecinosE2++;
	}

//Analizar posición 6
  if(posf+1 <= fil-1 and posc-1 >= 0)
	{
    if(mapa[posf+1][posc-1] == 1)
      vecinosE1++;
    else if(mapa[posf+1][posc-1] == 2)
      vecinosE2++;
	}

//Analizar posición 7
  if(posf+1 <= fil-1)
	{
    if(mapa[posf+1][posc] == 1)
      vecinosE1++;
    else if(mapa[posf+1][posc] == 2)
      vecinosE2++;
	}

//Analizar posición 8
  if(posf+1 <= fil-1 and posc+1 <= col-1)
	{
    if(mapa[posf+1][posc+1] == 1)
      vecinosE1++;
    else if(mapa[posf+1][posc+1] == 2)
      vecinosE2++;
	}

  return {vecinosE1, vecinosE2};
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {

	int vecinosE1 = analizarVecinos(f,c)[0];
	int vecinosE2 = analizarVecinos(f,c)[1];
	

	//Cuando hay una posición en cero
	  if(mapa[f][c] == 0)
            {
	     if(vecinosE1 >= vecinosE2)
		{
		if(vecinosE1 == 3)
		    nueva_conf[f][c] = 1;
		else
		    nueva_conf[f][c] = 0;
		}
	     else if(vecinosE2 > vecinosE1)
		{
		if(vecinosE2 == 3)
		    nueva_conf[f][c] = 2;
		else
		    nueva_conf[f][c] = 0;
		}
		
            }

	//Cuando hay una posición en uno
	  else if (mapa[f][c] == 1)
            { 
	      if(vecinosE1 >= vecinosE2)
		  {
	          if(vecinosE1 == 2 || vecinosE1 == 3)
		     nueva_conf[f][c] = 1;
                  else
		     nueva_conf[f][c] = 0;
		  }
	      else if(vecinosE2 > vecinosE1)
		  {
		  if(vecinosE2 == 3)
		     nueva_conf[f][c] = 2;
                  else
		     nueva_conf[f][c] = 0;
		  }     
            } 

	  //Cuando hay una posición en dos
	  else if (mapa[f][c] == 2)
            { 
	      if(vecinosE1 >= vecinosE2)
		  {
	          if(vecinosE1 == 3)
		     nueva_conf[f][c] = 1;
                  else
		     nueva_conf[f][c] = 0;
		  }
	      else if(vecinosE2 > vecinosE1)
		  {
		  if(vecinosE2 == 2 || vecinosE2 == 3)
		     nueva_conf[f][c] = 2;
                  else
		     nueva_conf[f][c] = 0;
		  }     
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

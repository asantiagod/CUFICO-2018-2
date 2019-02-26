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
  int vecinos;
  vector<vector<int> > mapa; //vector de dos componentes
  int contador2=0;
  int contador3=0;
 
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
 
  fil = f;
  col = c;
  mapa.resize(fil); //creando un vector del tamaño de las filas
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col); //creando una matriz
    }
 
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
      mapa[f][c] = rand()%2; // numero aleatorio entre cero y uno
        }
    }
}

void Mapa::dibujar()  // esta funcion recorre el mapa si encuentra un 1 pone * o un cero pone.
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
      cout << "\n"; // despues de barrer las columnas da un salto de linea
    }
}

int Mapa::analizarVecinos(int posf, int posc)
{
  vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0) // izquierda y abajo
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;
  if(posf-1 >= 0) //abajo misma columna
    if(mapa[posf-1][posc] == 1)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1) // abajo derecha
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;
  if(posc-1 >= 0) // misma fila columna anterior
    if(mapa[posf][posc-1] == 1)
      vecinos++;
  if(posc+1 <= col-1) // asegurando una columna al lado derecho
    if(mapa[posf][posc+1] == 1) //misma fila columna derecha
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

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa; // se creara un nuevo mapa
  int contador=0;
 
 
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
      int n_vecinos = analizarVecinos(f, c);
      if(mapa[f][c] == 0)
            {
          if(vecinos == 3)
               {
        nueva_conf[f][c] = 1;
                contador++;
                }
          else
        nueva_conf[f][c] = 0;
            }
      if (mapa[f][c] == 1)
            {
          if(vecinos == 2 || vecinos == 3)
                {
        nueva_conf[f][c] = 1;
                contador++;
                }
          else
        nueva_conf[f][c] = 0;
            }
        }
    }
    
    if (contador == contador2)
         {
         contador3++;
         
         }
 

  mapa = nueva_conf;
  contador2=contador;
}

int main()
{
 
 
  srand(time(NULL));
 
  int n;
  cout << "Por favor ingrese el valor de n: \n";
  cin >> n;
  Mapa mapa(60, 60); //recuerda cambiar el valor  de mapa
  int i=0;
  while(i < 2)
    {
      mapa.dibujar();
      //usleep(100000);
      system("clear");
        mapa.ciclo();
        i=mapa.contador3;
    }
         
}

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
  int vivos;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc); 
  int analizarVivos();
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

int Mapa::analizarVivos() //para poder usar la condición de estabilidad de las celdas vivas, este cuenta el número de celdas correspondientes a 1 en cada nueva configuración del sistema
{
	vector<vector<int> > nueva_conf = mapa;
	vivos = 0;
	for(int f=0; f<fil; f++)
	{
		for(int c=0; c<col; c++)
		{
		if(mapa[f][c] == 1)
		  vivos++;	
		}
	} 
	return vivos;
}

void Mapa::ciclo()
{
  vector<vector<int> > nueva_conf = mapa;
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

  mapa = nueva_conf;
}
/*Se integraron dos opciones para ingresar el número de n, si en la terminal solo se ingresa 1 argumento le pide
 * al usuario el n, si se ingresan dos toma el segundo argumento como el n.
 * como criterio de estabilidad se toma que el número de celdas vivas de la configuración anterior sea igual 
 * a la nueva, como el juego corre siempre y cuando "condicion" sea verdadera, una vez se cumple el criterio
 * "condicion" pasa a ser falsa, y hasta que no se cumpla se va reemplazando el número de celdad vivas de la configuracion vieja
 * con la nueva para una nueva comparación*/
int main(int arc, char *argv[])
{
  srand(time(NULL));
  bool condicion = true;
  int n_viejo = 0;
  int n_nuevo = 1;
  int N;
  
  if(arc == 2)
  N = atoi(argv[1]);
  else
  {
  cout << "Ingrese el número de filas y columnas n:" << endl;
  cin >> N;
  }
  Mapa mapa(N, N);
  
  while(condicion)
    { 
      //mapa.dibujar(); (para reducir el tiempo necesario en la toma de datos de omiten estas dos opciones)
      //usleep(1000000); 
      n_nuevo = mapa.analizarVivos();
      if(n_viejo == n_nuevo)
      condicion = false;
      else
      n_viejo = n_nuevo;
      system("clear");
      mapa.ciclo();
    }
}



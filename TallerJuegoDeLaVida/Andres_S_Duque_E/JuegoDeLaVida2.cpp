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
  int vecinos1; //Vecinos tipo 1
  int vecinos2; //Vecinos tipo 2
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc); //Retorna el número de vecinos
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
			mapa[f][c] = rand()%3; //Llenar con 0,1 o 2
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
				cout<< "o ";
			else
				cout << ". ";
		}
		cout << "\n";
	}
}

int Mapa::analizarVecinos(int posf, int posc)
{	 
	//  __ __ __
	// |v1|v2|v3|
	// |v4|  |v5|
	// |v6|v7|v8|
	//
	vecinos1 = 0;
	/*v1*/
	if(posf-1 >= 0 and posc-1 >= 0)
	{   
		if(mapa[posf-1][posc-1] == 1)
	    	vecinos1++;
		else if (mapa[posf-1][posc-1] == 2)
			vecinos2++;
	}

	/*v4*/
	if(posf-1 >= 0)
	{	
		if(mapa[posf-1][posc] == 1)
			vecinos1++;
		else if (mapa[posf-1][posc] == 2)
			vecinos2++;
	}

	/*v6*/
	if(posf-1 >= 0 and posc+1 <= col-1)
	{	
		if(mapa[posf-1][posc+1] == 1)
			vecinos1++;
		else if(mapa[posf-1][posc+1] == 2)
			vecinos2++;
	}

	/*v2*/
	if(posc-1 >= 0)
	{	
		if(mapa[posf][posc-1] == 1)
			vecinos1++;
		else if(mapa[posf][posc-1] == 2)
			vecinos2++;
	}

	/*v7*/
	if(posc+1 <= col-1)
	{	
		if(mapa[posf][posc+1] == 1)
			vecinos1++;
		else if(mapa[posf][posc+1] == 2)
			vecinos2++;
	}

	/*v3*/
	if(posf+1 <= fil-1 and posc-1 >= 0)
	{	
		if(mapa[posf+1][posc-1] == 1)
			vecinos1++;
		else if(mapa[posf+1][posc-1] == 2)
			vecinos2++;
	}

	/*v5*/
	if(posf+1 <= fil-1)
	{	
		if(mapa[posf+1][posc] == 1)
			vecinos1++;
		else if(mapa[posf+1][posc] == 2)
			vecinos2++;
	}

	/*v8*/
	if(posf+1 <= fil-1 and posc+1 <= col-1)
	{	
		if(mapa[posf+1][posc+1] == 1)
			vecinos1++;
		else if(mapa[posf+1][posc+1] == 2)
			vecinos2++;
	}

	return vecinos1 + vecinos2;
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
				if(n_vecinos == 3)
					nueva_conf[f][c] = (vecinos1 >= vecinos2)? 1 : 2;
				else
					nueva_conf[f][c] = 0;
			}
			else // mapa[f][c] == 1 || mapa[f][c] == 2
			{
				if(mapa[f][c] == 1 && vecinos2 == 3) //Reemplazar célula tipo 1
					nueva_conf[f][c] = 2;
				else if(mapa[f][c] == 2 && vecinos1 == 3) //Reemplazar célula tipo 2
					nueva_conf[f][c] = 1;
				else if(vecinos1 == 2 || vecinos1 == 3)
					nueva_conf[f][c] = 1;
				else if(vecinos2 == 2 || vecinos2 == 3)
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

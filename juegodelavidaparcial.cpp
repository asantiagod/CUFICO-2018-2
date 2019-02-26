#include <time.h> 
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
    vector<vector<int> > mapa;
    vector<vector<int> >     nueva_conf;
    Mapa(int f, int c);
    void dibujar();
    int analizarVecinos(int posf, int posc);
    void ciclo();
    int cuenta();
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

int Mapa::cuenta()
{
    int cuentas1=0;
    for (int f=0; f<fil; f++)
    {
        for(int c=0; c<col; c++)
        {
            if(mapa[f][c] == 1)
            {
                cuentas1++;
            }
        }
    }
    return cuentas1;
}

int main()
{
    float tiemponuevo=0;
    float tiempoviejo=0;
    int iteraciones=0;
    clock_t start, end; 
    srand(time(NULL));
    
    for (int n=5; n<60; n++)
    {
    	int start = clock(); 
	
	for(int k=1; k<51; )
    	{
                iteraciones=0;
    		Mapa mapa(n, n);
    		
		while(1)
    			{
                        //mapa.dibujar();
			//usleep(100000);
        		//system("clear");
        		int i=mapa.cuenta();
        		mapa.ciclo();
        		int j=mapa.cuenta();
          		float end = clock(); 
			iteraciones++;

			
        		if((i-j)==0){
          			tiemponuevo=end-tiempoviejo;
	  			tiempoviejo=end;
          			cout << tiemponuevo/CLOCKS_PER_SEC<<", ";
				k++;
          			break;
          			}

			if(iteraciones>10000000){
				//este if es un perro guardián para evitar que el código se caiga al encontrar un estado que no encaja con el criterio de estabilidad. 
				//k=k;
				exit(1);
				
				}	
        	}
	    
    	}
	cout<<"\n"<<endl;
    }
}

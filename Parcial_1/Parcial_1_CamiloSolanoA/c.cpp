#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <fstream>
using namespace std;

int get_int(){

	int n;
	cin >> n;
	while(cin.fail()) {
    	cout << "Ingrese un numero entero: \n" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> n;
    }
    cin.clear();
    cin.ignore(256,'\n');
    cout << "QQQQQQ";
    return n;
} 
class Mapa
{

public:
  int fil;
  int col;
  int vecinos;
  vector<vector<int> > mapa_old;
  
  vector<vector<int> > mapa;
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  int ciclo();
  
};

Mapa::Mapa(int f, int c){
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
    mapa_old=mapa;
    
}

void Mapa::dibujar()
{
  for(int f=0; f<fil; f++){
      for(int c=0; c<col; c++){
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

int Mapa::ciclo(){
	vector<vector<int> > nueva_conf = mapa;
  
  	for (int f=0; f<fil; f++){
      	for(int c=0; c<col; c++){

	  		int n_vecinos = analizarVecinos(f, c);
	  		if(mapa[f][c] == 0){

	      		if(vecinos == 3)
					nueva_conf[f][c] = 1;
	      		else
					nueva_conf[f][c] = 0;
        	}
	  		if (mapa[f][c] == 1){
	      		if(vecinos == 2 || vecinos == 3)
					nueva_conf[f][c] = 1;
	      	else
				nueva_conf[f][c] = 0;
      		}
      	}
    }
    
    for (int f=0; f<fil; f++){
      	for(int c=0; c<col; c++){
      		if(mapa[f][c] != nueva_conf[f][c]){

      			for (int f=0; f<fil; f++){
      				for(int c=0; c<col; c++){
      					if(nueva_conf[f][c]!=mapa_old[f][c]){

      						      mapa_old=mapa;
      						      mapa = nueva_conf;
      						      return 1;
                      
                    
                  
      					}
      				}
   				 }		
      		}
      	}
    }
     return 0;
	
	}

 
  



int main(int argc, char* argv[]){
  srand(time(NULL));
  
  if (argc==1){
    int f;
    int c;
    cout << "Ingrese el número de filas: \n";
    cin >>f;
	  cout << "Ingrese el numero de columnas: \n";
	  cin >>c;

    Mapa mapa(f,c);

    int running=1;
    int step=0;
    while(running && step <f*c){
      
        cout<<f<<" x "<<c<<endl;
        cout<<"paso: "<<step<<endl;
        mapa.dibujar();
        /*usleep(10000);*/
        system("clear");
      
      running=mapa.ciclo();
      step++;
    }
    cout << "El sistema se ha estabilizado    \n";

  }
	

  if (argc==6){
    
    int min_n=atoi(argv[1]);
    int max_n=atoi(argv[2]);
    int n_dat=atoi(argv[3]);
    ofstream file (argv[4]);

  for (int n=min_n;n<=max_n;n=n+5){
    for (int i=0;i<n_dat;i++){
    
      Mapa mapa(n,n);

      int running=1;
      int step=0;
      while(running && step <n*n*2){
        if (atoi(argv[5])){
          cout<<n<<" x "<<n<<endl;
          cout<<"paso: "<<step<<endl;
          mapa.dibujar();
          system("clear");
        }
        running=mapa.ciclo();
       step++;
      }
      file <<step-1<<", ";
      
  
      }
      file <<endl;
    }

    file.close();
  }
}
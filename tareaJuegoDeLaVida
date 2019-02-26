#include <iostream> //libreria para entrada y salida de datos
#include <cstdlib>  //libreria para el uso de numeros aleatoreos
#include <vector> //libreria para el uso de vectores
#include <unistd.h> //librerria para el manejo dinamico de la memoria

using namespace std; //se usa para poder imprimir caracteres en pantalla

class Mapa //se declara una clase de nombre Mapa
{
public:  //se van a definir datos publicos
  int fil; //define filas como un entero
  int col; //define columnas como un entero
  int vecinos;  //define los vecionos como enteros
  vector<vector<int> > mapa; //define un vector entero dentro de otro vector, llamado mapa. Sirve para la ubicacion sobre la red
  
  Mapa(int f, int c); //se inicializa la clase Mapa con dos entradas enteras
  void dibujar(); //funcion vacia llamada dibujar
  int analizarVecinos(int posf, int posc); //funcion entera con dos entradas enteras llamada analizar vecinos
  void ciclo();//funcion vacia llamada ciclo
};

Mapa::Mapa(int f, int c) //se define la clase Mapa
{
  fil = f; //fil es el valor entero f que se define en la clase
  col = c; //col es le valor entero c que se define en la clase
  mapa.resize(fil); //el vector mapa toma un tamaño igual a fil en sus filas
  for(int i=0; i<mapa.size(); i++) //barre todas las entradas de las filas
    {
      mapa[i].resize(col); //para cada entrada de la fila se da un tamaño para el vector dentro de las filas de tamaño col
    }
  
  for(int f=0; f<fil; f++) //barre las filas de la red
    {
      for(int c=0; c<col; c++) //barre las columbas de la red
        {
	  mapa[f][c] = rand()%2; // para cada entrada en la red pone de manera aleatorea 0 o 1
        }
    }
}

void Mapa::dibujar() //se define la funcion dibujar dentro de la clase Mapa
{
  for(int f=0; f<fil; f++)  //barre las filas de la red
    {
      for(int c=0; c<col; c++) //barre las columnas de la red
        {
	  if(mapa[f][c] == 1)  //si la entrada de la red es igual a 1
	    cout << "* ";      //pone un * 
	  else                 //sino
	    cout << ". ";      //pone un .
        }
      cout << "\n";            //al terminar la primera columna se escribe un enter para seguir con la proxima
    }
}

int Mapa::analizarVecinos(int posf, int posc) //se define la funcion analizarVecinos dentro de la clase Mapa
{
  vecinos = 0;  //se inicia la variable vecinos con un cero
  if(posf-1 >= 0 and posc-1 >= 0) //busca la entrada de la red que es vecino del punto estudado, ubicado en la esquina superior izquierda
    if(mapa[posf-1][posc-1] == 1) //y ademas si en esta ubicacion hay un uno
      vecinos++;                  //a la variable vecino se le suma 1
  if(posf-1 >= 0)                 //busca la entrada de la red que es vecino del punto estudiado, ubicado arriba
    if(mapa[posf-1][posc] == 1)   //si en esta ubicacion hay un uno
      vecinos++;                  //a la variable vecino se le suma uno
  if(posf-1 >= 0 and posc+1 <= col-1) //busca la entrada de la red que es vecino del punto estudado, ubicado en la esquina superior derecha
    if(mapa[posf-1][posc+1] == 1)     //si en esta ubicacion hay un uno
      vecinos++;                      //a la variable vecino se le suma uno
  if(posc-1 >= 0)                     //busca la entrada de la red que es vecino del punto estudiado, ubicado al lado izquierdo
    if(mapa[posf][posc-1] == 1)       //si en esta ubicacion hay un uno    
      vecinos++;                      //a la variable vecino se le suma uno
  if(posc+1 <= col-1)                 //busca la entrada de la red que es vecino del punto estudiado, ubicado al lado derecho
    if(mapa[posf][posc+1] == 1)       //si en esta ubicacion hay un uno   
     vecinos++;                       //a la variable vecino se le suma uno
  if(posf+1 <= fil-1)                 //busca la entrada de la red que es vecino del punto estudiado, ubicado abajo
    if(mapa[posf+1][posc] == 1)       //si en esta ubicacion hay un uno 
      vecinos++;                       //a la variable vecino se le suma uno
  if(posf+1 <= fil-1 and posc+1 <= col-1) //busca la entrada de la red que es vecino del punto estudado, ubicado en la esquina inferior derecha
    if(mapa[posf+1][posc+1] == 1)         //si en esta ubicacion hay un uno
      vecinos++;                          //a la variable vecino se le suma uno
  if(posf+1 <= fil-1 and posc-1 <= 0) //busca la entrada de la red que es vecino del punto estudado, ubicado en la esquina inferior izquierda
    if(mapa[posf+1][posc-1] == 1)         //si en esta ubicacion hay un uno
      vecinos++;                          //a la variable vecino se le suma uno
  return vecinos;
}

void Mapa::ciclo()  //se define la funcion ciclo dentro de la clase Mapa
{
  vector<vector<int> > nueva_conf = mapa; //define un vector dentro de otro vector y lo llama nueva configuracion, este vector es igual al vertor mapa
  
  for (int f=0; f<fil; f++)  //barre todas las filas
    {
      for(int c=0; c<col; c++) //barre todas las columnas
        {
	  int n_vecinos = analizarVecinos(f, c); //define un entero n_vecinos que es igual al numero que arroja la funcion analizarVecinos
	  if(mapa[f][c] == 0) //si la entrada evaluada es igual a cero
            {
	      if(vecinos == 3)//si ademas el numero de vecinos es tres
		nueva_conf[f][c] = 1; //cambie la entrada por un uno
	      else                   //sino
		nueva_conf[f][c] = 0; //cambie la entrada por un cero
            }
	  if (mapa[f][c] == 1) //si la entrada evaluada es igual a uno
            {
	      if(vecinos == 2 || vecinos == 3)//si ademas el numero de vecinos es dos o tres
		nueva_conf[f][c] = 1;  //cambie la entrada por un uno
	      else                     //sino
		nueva_conf[f][c] = 0;  //cambie la entrada por un cero
            }
        }
    }
  
  mapa = nueva_conf;  //cambie el vertor mapa por el nuevo vector nueva_conf
}

int main()  //funcion principal
{
  srand(time(NULL)); //inicia el fenerador de numeros aleatoreos
  Mapa mapa(50, 50); //llama a la clase mapa con argumentos 50 y 50
  while(1)  //ciclo infinito
    {
      mapa.dibujar(); //llama a la funcion dibujar de la clase mapa
      usleep(100000); //hace una pausa de 100000 microsegundos
      system("clear"); //limpia la ventana antes de volver a mostrar el mapa
        mapa.ciclo();  //llama a la funcion ciclo de la clase mapa
    }
}

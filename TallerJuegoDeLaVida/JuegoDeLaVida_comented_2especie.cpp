#include <iostream>  //incluir libreria para operaciones de entrada y salida
#include <cstdlib>  //Incluir libreria para control de memoria
#include <vector>  //Inicializar un vector vacio
#include <unistd.h> //Incluir la libreria unistd.h

using namespace std;  //Incluir las palabras del diccionario estandar de C++

class Mapa //declarar la clase mapa
{
public: //Declarar las funciones que se pueden usar fuera de la clase Mapa
  int fil; //Declarar el atributo fila de tipo entero
  int col; // declarar el atributo columna de tipo entero
  int tipo1; //declarar el atributo tipo1 como entero
  int tipo2; //declarar el atributo tipo2 como entero
  vector<vector<int> > mapa; //declara una matriz de numeros enteros cuyo nombre es mapa
  
  Mapa(int f, int c); //declara la funcion mapa que recibe dos enteros f y c
  void dibujar(); //declara la funcion dibujar
  int analizarVecinos(int posf, int posc); //declara la funcion analizarVecinos, recibe dos enteros posf y posc
  void ciclo(); //declara la funcion ciclo
};

Mapa::Mapa(int f, int c) //Definicion de la funcion Mapa de la clase Mapa
{
  fil = f; //Para la funcion se define fil como f
  col = c; //Para la funcion se define col como c
  mapa.resize(fil); //redefine el tamaño de la matriz mapa
  for(int i=0; i<mapa.size(); i++) //Ciclo  con el cual se llena cada elemento del vector con otro vector
    {
      mapa[i].resize(col); //Se define el tañamo de la entrada de cada elemento del vector con el numero de columnas
    }
  
  for(int f=0; f<fil; f++) //Se inicia un ciclo para barrer las filas
    {
      for(int c=0; c<col; c++)  //Se inicia un ciclo para barrer las columnas
        {
	  mapa[f][c] = rand()%3; //A cada elemento de la matriz se le asigna un numero aleatorio que puede ser cero, uno o dos, esto depende del modulo 3 de un numero aleatorio natural
        }
    }
}

void Mapa::dibujar() //Definicion de la funcion dibujar de la clase Mapa
{
  for(int f=0; f<fil; f++) //Se inicia un ciclo para barrer las filas
    {
      for(int c=0; c<col; c++) //Se inicia un ciclo para barrer las columnas
        {
	  if(mapa[f][c] == 1) //Si en la entrada de la matriz hay un uno, se imprime *
	    cout << "* ";
	  else if(mapa[f][c] == 2) //Si en la entrada de la matriz hay un dos, se imprime ~
	    cout << "~ ";
	  else //Si en la entrada de la matriz hay un cero, se imprime .
	    cout << ". ";
        }
      cout << "\n"; //Cuando se barre una fila se agrega un salto de linea
    }
}

int Mapa::analizarVecinos(int posf, int posc) 
// Definicion de la funcion analizarVecinos de la clase mapa, recibe la posicion de la fila y de la columna de la entrada de la matriz
{
  tipo1 = 0; //Se inicializa la variable tipo1 con un cero
  tipo2 = 0; //Se inicializa la variable tipo2 con un cero
  
  if(posf-1 >= 0 and posc-1 >= 0) // si la fila es mayor o igual que la segunda y la columna es mayor o igual que la segunda
    if(mapa[posf-1][posc-1] == 1) //si en la diagonal superior izquierda de la entrada hay un uno, en ese caso se adiciona a tipo1 si hay un uno
      tipo1++; 
    else if(mapa[posf-1][posc-1] == 2) //si en la diagonal superior izquierda de la entrada hay un dos, en ese caso se adiciona a tipo2 si hay un uno
      tipo2++;
      
      
  if(posf-1 >= 0) //Si la fila es mayor o igual que la segunda
    if(mapa[posf-1][posc] == 1)  //Si arriba de la entrada hay un uno se incrementa el contador tipo1
      tipo1++;
    else if(mapa[posf-1][posc] == 2)//Si arriba de la entrada hay un dos se incrementa el contador tipo2
      tipo2++;
      
      
  if(posf-1 >= 0 and posc+1 <= col-1) // si la fila es mayor o igual que la segunda y la posicion de la columna mas dos es menor o igual que el numero de columnas
    if(mapa[posf-1][posc+1] == 1) // Si en la esquina superior derecha haya un uno, en este caso se adiciona a tipo1
      tipo1++;
    else if(mapa[posf-1][posc+1] == 2) // Si en la esquina superior derecha haya un uno, en este caso se adiciona a tipo2
      tipo2++;
      
      
  if(posc-1 >= 0) //Si la columna es mayor o igual que la segunda
    if(mapa[posf][posc-1] == 1)  //Si a la izquierda de la entrada hay un uno se incrementa el contador tipo1
      tipo1++;
    else if(mapa[posf][posc-1] == 2)  //Si a la izquierda de la entrada hay un dos se incrementa el contador tipo2
      tipo2++;
      
      
  if(posc+1 <= col-1) //Si la columna más dos es menor o igual que el numero de columnas
    if(mapa[posf][posc+1] == 1) //Si a la derecha de la entrada hay un uno se incrementa el contador tipo1
      tipo1++;
    else if(mapa[posf][posc+1] == 2) //Si a la derecha de la entrada hay un dos se incrementa el contador tipo2
      tipo2++;
      
      
  if(posf+1 <= fil-1 and posc-1 >= 0) //Si la posicion de la fila más dos es menor o igual que el numero de filas y la columna es mayor o igual que la segunda
    if(mapa[posf+1][posc-1] == 1) //Si en la esquina inferior izquierda hay un uno, se añade al contador tipo1
      tipo1++;
    else if(mapa[posf+1][posc-1] == 2) //Si en la esquina inferior izquierda hay un dos, se añade al contador tipo2
      tipo2++;
      
      
  if(posf+1 <= fil-1) //Si la posicion de la fila más dos es menor o igual que el numero de filas 
    if(mapa[posf+1][posc] == 1) //Si debajo de la entrada hay un uno, se añade al contador tipo1
      tipo1++;
    else if(mapa[posf+1][posc] == 2) //Si debajo de la entrada hay un dos, se añade al contador tipo2
      tipo2++;
      
      
  if(posf+1 <= fil-1 and posc+1 <= col-1) //Si la posicion de la fila más dos es menor o igual que el numero de filas  y la columna mas dos es menor o igual que el numero de columnas
    if(mapa[posf+1][posc+1] == 1) //si en la diagonal derecha inferior hay un uno se añade al contador tipo1
      tipo1++;
    else if(mapa[posf+1][posc+1] == 2) //si en la diagonal derecha inferior hay un dos se añade al contador tipo2
      tipo2++;
           
  return 0;
  
  }

void Mapa::ciclo() // Con esta funcion de la clase mapa, se barren las filas y las columnas
{
  vector<vector<int> > nueva_conf = mapa; // se inicializa una configuración de mapa
  
  for (int f=0; f<fil; f++) //con este ciclo se barre sobre las filas
    {
      for(int c=0; c<col; c++) //con este ciclo se barre sobre las columnas
        {
	  analizarVecinos(f, c); //se declara como entero n_vecinos, el cual proviene de la funcion analizarVecinos
	  
	  if(mapa[f][c] == 0) //Condiciones bajo las cuales se transforma una celda cuya entrada es 0
            {
	      if(tipo1 == 3 ) 
		nueva_conf[f][c] = 1; 
		    else if(tipo2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0; 
            }
            
            
    if(mapa[f][c] == 1) //Condiciones bajo las cuales se transforma una celda cuya entrada es 1
            {
		    if(tipo1 >= tipo2 && (tipo1 == 3 || tipo1 == 2))
		nueva_conf[f][c] = 1;
		    else if(tipo2 > tipo1 && tipo2 == 3)
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0; 
            }            
            
    if(mapa[f][c] == 2) //Condiciones bajo las cuales se transforma una celda cuya entrada es 2
            {
		    if(tipo1 >= tipo2 && tipo1 == 3 )
		nueva_conf[f][c] = 1;
		    else if(tipo2 > tipo1 && (tipo2 == 3 || tipo2 == 2))
		nueva_conf[f][c] = 2;
	      else
		nueva_conf[f][c] = 0; 
            }    
          
    tipo1 = 0; //Se reinician a ceros los contadores tipo1 y tipo2 de la estructura
    tipo2 = 0;
        }        
    }
    
  
  mapa = nueva_conf;// el mapa se redefine de acuerdo a la configuración anterior
}

int main() //Se define la función principal
{
  srand(time(NULL)); //genera una semilla para numeros aleatorios con base en el tiempo interno del computador
  Mapa mapa(50, 50); //inicia la función mapa de la clase Mapa con cincuenta filas y cincuenta columnas
  while(1) //Para la ejecución del ciclo
    {
      mapa.dibujar(); //se dibuja la matriz
      usleep(100000); //se le añade un delay 
      system("clear"); //limpia la pantalla para la nueva configuracion
        mapa.ciclo(); //se corre la función ciclo de la clase Mapa
    }
}

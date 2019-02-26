// cabecera con declaraciones de funciones y constantes para manejar entrada y salida
#include <iostream>
// se incluyen funciones de la libreria estandar> srand, time, system,...
#include <cstdlib>
// libreria con funciones para manejar vectores de forma eficiente
#include <vector>
// incluye funciones y constantes varias para controlar el sistema, la funcion usleep por ejemplo
#include <unistd.h>


// para no escribir std:, esta linea trae todo los nombre del espacio de nombres std
// al espacio de nombre global
using namespace std;


// definicion de la clase map que sirve para el tablero
class Mapa{
// para definir miembros de clase como publico, cualquier objeto puede acceder a
// ellos desde afuera
public:
    // atributos. Numero filas, columnas, y numero de vecinos
    int fil;
    int col;
    int vecinos;
    // se define un vector de vectores de enteros para representar el tablero
    vector<vector<int> > mapa;

    // constructor de la clase, recibe numero de filas y numero de columnas
    Mapa(int f, int c);
    // funcion para dibujar en pantalla
    void dibujar();
    // funcion que cuenta cuantos vecinos vivos tiene la celula de tipo typeen la posicion (porf, posc)
    int analizarVecinos(int posf, int posc, int type);
    // funcion que actualiza el estado del mapa
    void ciclo();
};


// este constructor llena la matriz con celulas aleatorias
Mapa::Mapa(int f, int c){
    fil = f;  // almacena numero de filas
    col = c;  // almacena numero de columnas
    mapa.resize(fil);  // se le da espacio de n componentes a mapa para almacenar las filas
    for(int i = 0; i < mapa.size(); i++){  // se recorre cada componente de mapa
        // en cada componente se almacena un vector con numero de  entradas igual a numero columnas
        mapa[i].resize(col);
    }
  
    // este for recorre el numero de filas
    for(int f = 0; f < fil; f++){
        // recorre el numero de columnas
        for(int c = 0; c < col; c++){
            // se pone una celula aleatoria en la componente (f, c)
            mapa[f][c] = rand() % 3;
        }
    }
}



// metodo que muestra en pantalla el tablero
void Mapa::dibujar(){
    // se itera sobre el numero de filas del mapa
    for(int f = 0; f < fil; f++){
        // se itera sobre el numero de columnas 
        for(int c=0; c<col; c++){
            // si hay una celula viva de tipo 1 se imprime o
	        if(mapa[f][c] == 1)
	            cout << "o ";
            // si hay una celula viva de tipo 2 se imprime x
            else if(mapa[f][c] == 2)
                cout << "x ";
            // celula, muerta imprime .
            else
	            cout << ". ";
        }
        // agrega salto de linea
        cout << "\n";
    }
}


// funcion que cuenta los vecinos vivos
int Mapa::analizarVecinos(int posf, int posc, int type){
    vecinos = 0;
    // cuanta los vecinos vivos teniendo en cuenta los limites de la matrix
    // si esta vivo se suma al numero de vecinos
    // para celulas que no estan en el borde izquierdo y borde superior
    if(posf - 1 >= 0 and posc - 1 >= 0) 
        if(mapa[posf - 1][posc - 1] == type)
            vecinos++;
    // celulas que no estan en el borde superior
    if(posf - 1 >= 0)
        if(mapa[posf - 1][posc] == type)
            vecinos++;
    // celulas que no estan en el borde superior y borde derecho
    if(posf - 1 >= 0 and posc + 1 <= col - 1)
        if(mapa[posf - 1][posc + 1] == type)
            vecinos++;
    // celulas que no estan en el borde superior
    if(posc - 1 >= 0)
        if(mapa[posf][posc - 1] == type)
            vecinos++;
    // celulas que no estan en el borde derecho
    if(posc + 1 <= col - 1)
        if(mapa[posf][posc + 1] == type)
            vecinos++;
    // celulas que no estan en el borde izquierdo y borde inferior
    if(posf + 1 <= fil - 1 and posc - 1 >= 0)
        if(mapa[posf + 1][posc - 1] == type)
            vecinos++;
    // celulas que no estan en el borde inferior
    if(posf + 1 <= fil - 1)
        if(mapa[posf + 1][posc] == type)
            vecinos++;
    // celulas que no estan en el borde inferior y borde derecho
    if(posf + 1 <= fil - 1 and posc + 1 <= col - 1)
        if(mapa[posf + 1][posc + 1] == type)
            vecinos++;

    return vecinos;
}


// funcion que aplica las reglas de transicion, homogeneamente al sistema
void Mapa::ciclo(){
    // se crea una vector de vectores para almacenar el nuevo estado del tablero
    vector<vector<int> > nueva_conf = mapa;
  
    // se itera sobre el numero de filas
    for(int f = 0; f < fil; f++){
        // se itera sobre el numero de columnas
        for(int c = 0; c < col; c++){
            // se cuenta el numero de vecinos de tipo 1 y 2 de la celula en la posicion (f, c)
	        int n_vecinos1 = analizarVecinos(f, c, 1);
            int n_vecinos2 = analizarVecinos(f, c, 2);
            // se aplican las reglas
            if(mapa[f][c] == 0){
                if(n_vecinos1 == 3) 
                    nueva_conf[f][c] = 1;  // regla para el nacimiento
                else if(n_vecinos2 == 3)
                    nueva_conf[f][c] = 2;
	            else
                    nueva_conf[f][c] = 0;  // si no tiene vivos sigue muerto
            }
	        if (mapa[f][c] == 1){
	            if(n_vecinos1 >= n_vecinos2 && (n_vecinos1 == 2 || n_vecinos1 == 3))
		            nueva_conf[f][c] = 1;  // continua vivo si tiene 2 o 3 vivos
                else if(n_vecinos2 > n_vecinos1 && n_vecinos2 == 3)
                    nueva_conf[f][c] = 2;  // en caso de que vivos de tipo 2 sea 3 se reemplaza 1 por 2
	            else
		            nueva_conf[f][c] = 0;  // muere por sobrepoblacion
            }
            if (mapa[f][c] == 2){
                if (n_vecinos1 >= n_vecinos2 && n_vecinos1 == 3)  // tipo 1 prevalece ante el 2
                    nueva_conf[f][c] = 1;
                else if (n_vecinos2 > n_vecinos1 && (n_vecinos2 == 2 || n_vecinos2 == 3))
                    nueva_conf[f][c] = 2;  // continua vivo si tiene 2 o 3 vivos
                else
                    nueva_conf[f][c] = 0;  // muere por sobrepoblacion
            }   
        }
    }
    // se actualiza el sistema
    mapa = nueva_conf;
}


// funcion principal, se ejecuta al empezar el programa
int main(){
    // inicializa la semilla para generar numeros aleatorios
    srand(time(NULL));
    // se crea el objeto encargado de manejar el tablero del sistema
    Mapa mapa(50, 50);
    // mantiene el programa en ejecucion, ciclo infinito
    while(1){
        // dibuja el mapa en pantalla
        mapa.dibujar();
        // suspende la ejecucion 100000 este tiempo en microsegundos
        usleep(100000);
        // limpia la pantalla
        system("clear");
        // actualiza el tablero, aplica las reglas de transicion
        mapa.ciclo();
    }
}

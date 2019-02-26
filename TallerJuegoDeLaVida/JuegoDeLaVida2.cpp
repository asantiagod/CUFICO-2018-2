//Incluir librerias
#include <iostream> //Libreria para acciones de entrada/salida de datos.
#include <cstdlib>
#include <vector> //Libreria para manipular arreglos.
#include <unistd.h>

using namespace std;

//Declaracion de la clase Mapa.
class Mapa {
    //Tipo de acceso de la clase.
public:
    //Atributo fila en la que se encuentra un individuo de la especie.
    int fil;
    //Atributo columna en la que se encuentra un individuo de la especie.
    int col;
    //Numero de vecinos del individuo.
    int vecinos;
    //Matriz de posiciones, la cual representa el mapa.
    vector<vector<int> > mapa;
    //Metodo Mapa.
    Mapa(int f, int c);
    //Implementacion metodo dibujar.
    void dibujar();
    //Funcion analizar vecinos.
    vector<int> analizarVecinos(int posf, int posc);
    //Metodo ciclo
    void ciclo();
};

//Método mapa, en el que se inicializa el mapa como matiz de f*c y se llena aleatoriamente.
Mapa::Mapa(int f, int c)
{
    //Numero de filas del mapa
    fil = f;
    //Numero de columnas del mapa
    col = c;
    //Se dimensiona el vector mapa para que tenga f vectores.
    mapa.resize(fil);
    for (int i = 0; i < mapa.size(); i++) {
        mapa[i].resize(col); //Cada vector del mapa se dimensiona para que tenga c elementos.
    }

    for (int f = 0; f < fil; f++) {
        for (int c = 0; c < col; c++) {
            mapa[f][c] = rand() % 3; //Se llena cada posicion del mapa de manera aleatoria con numeros entre 0 y 2.
        }
    }
}

//Metodo para dibujar en consola el mapa
void Mapa::dibujar()
{
    //Se recorre por filas
    for (int f = 0; f < fil; f++) {
        //Se recorren por columnas
        for (int c = 0; c < col; c++) {

            if (mapa[f][c] == 1) {
                cout << "* "; //Si en la fila f, columna c, se encuentra la especie 1, entonces esta es representada mediante "*"
            }
            else if (mapa[f][c] == 2) {
                cout << "- "; //Si en la fila f, columna c, se encuentra la especie 2, entonces esta es representada mediante "-"
            }
            else {
                cout << ". "; //En caso contrario, se muestra un "."
            }
        }
        cout << "\n"; //Salto de línea
    }
    cout << "\n";
}
//Funcion que analiza los vecinos de un individuo dada su posicion.
vector<int> Mapa::analizarVecinos(int posf, int posc)
{
    //Contador de número de vecinos
    vector<int> vecinos = { 0, 0 };
    //Se analiza cada una de las 8 posiciones adyacentes a la posicion actual
    if (posf - 1 >= 0 and posc - 1 >= 0) {
        if (mapa[posf - 1][posc - 1] == 1) //Si hay un vecino, entonces se aumenta el contador
            vecinos[0]++;
        if (mapa[posf - 1][posc - 1] == 2) //Si hay un vecino, entonces se aumenta el contador
            vecinos[1]++;
    }
    if (posf - 1 >= 0) {
        if (mapa[posf - 1][posc] == 1)
            vecinos[0]++;
        if (mapa[posf - 1][posc] == 2)
            vecinos[1]++;
    }
    if (posf - 1 >= 0 and posc + 1 <= col - 1) {
        if (mapa[posf - 1][posc + 1] == 1)
            vecinos[0]++;
        if (mapa[posf - 1][posc + 1] == 2)
            vecinos[1]++;
    }
    if (posc - 1 >= 0) {
        if (mapa[posf][posc - 1] == 1)
            vecinos[0]++;
        if (mapa[posf][posc - 1] == 2)
            vecinos[1]++;
    }
    if (posc + 1 <= col - 1) {
        if (mapa[posf][posc + 1] == 1)
            vecinos[0]++;
        if (mapa[posf][posc + 1] == 2)
            vecinos[1]++;
    }
    if (posf + 1 <= fil - 1 and posc - 1 >= 0) {
        if (mapa[posf + 1][posc - 1] == 1)
            vecinos[0]++;
        if (mapa[posf + 1][posc - 1] == 2)
            vecinos[1]++;
    }
    if (posf + 1 <= fil - 1) {
        if (mapa[posf + 1][posc] == 1)
            vecinos[0]++;
        if (mapa[posf + 1][posc] == 2)
            vecinos[1]++;
    }
    if (posf + 1 <= fil - 1 and posc + 1 <= col - 1) {
        if (mapa[posf + 1][posc + 1] == 1)
            vecinos[0]++;
        if (mapa[posf + 1][posc + 1] == 2)
            vecinos[1]++;
    }
    return vecinos; //Se devuelve la cantidad de vecinos.
}
//Metodo en el que se analiza cada posicion del mapa para contar el numero de vecinos y aplicar las reglas del juego de la vida
void Mapa::ciclo()
{

    //Mapa actualizado una vez aplicadas las reglas del juego
    vector<vector<int> > nueva_conf = mapa;

    //Se recorre por filas el mapa
    for (int f = 0; f < fil; f++) {
        //Se recorre por columnas el mapa
        for (int c = 0; c < col; c++) {
            //Se encuentra el numero de vecinos para el individuo en la fila f y la columna c

            vector<int> vecinos = analizarVecinos(f, c);
            int i = 0;
            int val = mapa[f][c];
            if (vecinos[1] > vecinos[0])//Se mira cual de las dos especies gana
                i = 1;
            if (val == 0) //Si en la posicion no hay ningun individuo
            {
                if (vecinos[i] == 3) //Y el numero de vecinos es 3
                    nueva_conf[f][c] = i + 1; //Entonces esta posicion es poblada con un individuo
                else
                    nueva_conf[f][c] = 0; //Sino, se deja vacio
            }
            else if (val == 1) //Si en la posicion hay un individuo,
            {
                if (vecinos[0] == 2 || vecinos[0] == 3) //Y tiene 2 o 3 vecinos, entonces sobrevive
                    nueva_conf[f][c] = 1; //Sino, muere
                else if (vecinos[1] == 3)//Si tiene tres vecinos de la otra especie
                    nueva_conf[f][c] = 2;//Esta especie ocupa el lugar
                else
                    nueva_conf[f][c] = 0;
            }
            else if (val == 2) //Si en la posicion hay un individuo,
            {
                if (vecinos[1] == 2 || vecinos[1] == 3) //Y tiene 2 o 3 vecinos, entonces sobrevive
                    nueva_conf[f][c] = 2; 
                else if (vecinos[0] == 3) //Si tiene tres vecinos de la otra especie
		    nueva_conf[f][c] = 1;//Esta especie ocupa el lugar
		else
                    nueva_conf[f][c] = 0;//Sino, muere
                   
            }
        }
    }

    mapa = nueva_conf; //Actualiza la matriz mapa
}

//Metodo principal
int main()
{
    srand(time(NULL)); ////Función para inicializar el generator de numeros aleatorios.
    Mapa mapa(50, 50); //Instancia de la clase mapa, con 50 filas y 50 columnas
    while (1) //Se repite de manera indefinida
    {
        mapa.dibujar(); //Se dibuja el mapa en pantalla
        usleep(100000); //Establece un tiempo de espera
        system("clear"); //Limpia la consola
        mapa.ciclo(); //Se recorre el mapa
    }
}

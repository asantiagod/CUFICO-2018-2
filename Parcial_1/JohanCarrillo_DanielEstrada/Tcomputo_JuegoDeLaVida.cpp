  /*
Este codigo ejecuta el juego de la vida y se detiene cuando el sistema se estabiliza. 
Durante el proceso se calcula el timepo de computo y se escribe en un archivo de texto. 
Esto se hace 20 veces para un tamaño de matriz determinado por el usuario.

Los criterios de estabilidad que se escogieron fueron: 
  - Que durante 5 ciclos seguidos el numero de celulas vivas fuera el mismo
  - Que se llegue a un buble de periodo 2 o 3

Se eligieron estos pues fueron los que mas se notaron al realizar el ejercicio. No obstante la aparicíon de un buble
afecta mucho el tiempo de estabilizacion del sistema, lo que llevara luego a que los datos de tiempo para un mismo n sean
bastante disparejos y el ajuste con la gaussiana va a quedar muy feo.

El programa le pregunta al usuario el tamaño n que quiere para la matriz, se dieron 12 valores de n entre 5 y 60 igualmente
espciados y cada n se repitio 20 veces, estos 20 valores se guardan en un archivo .txt que se usara luego
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <stdio.h>

using namespace std;

class Mapa
{
public:
  int fil;  // Numero de filas
  int col;  //Numero de columnas
  int vecinos;  //  Atributo quesirve para contar el numero de vecinos vivos que tiene una sola celula
  int N_Vivos; // Atributo que tiene la informacion de cuantos vivos hay por ciclo 
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  void ciclo();
};

Mapa::Mapa(int f, int c)
{
  // Esta funcion sirve para pintar el mapa por primera vez y darle valores iniciales aleatorios a cada entrada
  N_Vivos = 0;
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
           if (mapa[f][c] == 1)
            N_Vivos++; // esta linea cuenta el numero de vivos al establecer el arreglo inical
        }
    }
}

void Mapa::dibujar()
{
    // Esta funcion imprime el mapa en la terminal
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
    if(mapa[f][c] == 1)
      cout << "* ";  // Representa las celulas vivas
    else
      cout << ". ";  // Representa las celulas muertas
        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos(int posf, int posc)
{
    // Esta funcion evalua las condiciones de frontera para cada celula y cuenta el numero de vecinos vivos que tiene
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
    // Esta funcion calcula el valor de cada entrada de la matriz para el paso siguiente de tiempo
  vector<vector<int> > nueva_conf = mapa;  // Guarda la nueva forma del mapa
  N_Vivos = 0;  // se reinicia el contador de vivos para recalcularse 
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
    int n_vecinos = analizarVecinos(f, c);
    if(mapa[f][c] == 0)
      // Se evaluan las condiciones si la celula esta muerta
            {
        if(vecinos == 3){
    nueva_conf[f][c] = 1;
    N_Vivos++; // aumenta el numero de vivos 
    }
        else
    nueva_conf[f][c] = 0;
            }
    if (mapa[f][c] == 1)
      // Se evaluan las condiciones si la celula esta viva
            {
        if(vecinos == 2 || vecinos == 3){
    nueva_conf[f][c] = 1;
    N_Vivos++; 
    }
        else
    nueva_conf[f][c] = 0;
            }
        }
    }
  
  mapa = nueva_conf;
}

int main()
{
  int n;
  char nombre_archivo[30];  // Se usa para generar los nombres de los archivos que se guardaran

  cout << "Ingrese el tamaño de la matriz: \n ";
  cin >> n ;  // Se lee el tamaño de la matriz

  sprintf(nombre_archivo, "Datos_TComputo/Tiempo_Computo_%d.txt", n);
  FILE *archivo = fopen(nombre_archivo, "w");  // Se genera y se abre el archivo .txt

  for (int i = 0; i < 20; i++){
    // Este ciclo calcula para el mismo valor de n, 20 veces el tiempo de estabilizacion
    clock_t t;  
    t = clock();  // Se inicia el reloj
    
    int  k=0;  
    int vivos[10]; // arreglo en el que se almacena el numero de vivos de los 10 ultimos ciclos 
    
    srand(time(NULL));
    Mapa mapa(n, n);

    while(1)
      {
        /* En este ciclo se evoluciona el sistema hasta que se satisfaga alguna de las condiciones de parado, si se observa
        algun bucle de periodo mayor a 3 se tiene que reiniciar el codigo manualmente y volver a empezar*/
        mapa.dibujar();
        usleep(10000);
        system("clear");
        
        vivos[k] = mapa.N_Vivos;
        mapa.ciclo();
        
        if(k == 9){
          // luego de hacer 10 ciclos se evalua si el numero de vivos es estable o no
          if(vivos[5] == vivos[6] && vivos[5] == vivos[7] && vivos[5] == vivos[8] && vivos[5]==vivos[9]){
            t = clock() - t;
            break; // si se estabiliza se rompe el proceso
          }
          else if((vivos[0]==vivos[2] && vivos[0]==vivos[4] && vivos[0]==vivos[6]) 
            && (vivos[1]==vivos[3] && vivos[1]==vivos[5] && vivos[1]==vivos[7])){
            t = clock() - t;
            break;
          }
          else if((vivos[0]==vivos[3] && vivos[0]==vivos[6] && vivos[0]==vivos[9]) 
            && (vivos[1]==vivos[4] && vivos[1]==vivos[7]) && (vivos[2]==vivos[5] && vivos[2]==vivos[8])) {
            t = clock() - t;
            break;
          }          

          else{
            // sino se cumple la estabilidad se reordenan los elementos del arreglo vivos para incluir una iteración más del while
            vivos[0] = vivos[1];
            vivos[1] = vivos[2];
            vivos[2] = vivos[3];
            vivos[3] = vivos[4];
            vivos[4] = vivos[5];
            vivos[5] = vivos[6];
            vivos[6] = vivos[7];
            vivos[7] = vivos[8];
            vivos[8] = vivos[9];
            k = 8;
          }  
        }
        k++;
      }

    fprintf(archivo, "%f \n",((float)t) / CLOCKS_PER_SEC);  // Se copia el valor del tiempo de estabilizacion en el .txt
  }

  fclose(archivo);  // Se cierra el archivo


  return 0;
}
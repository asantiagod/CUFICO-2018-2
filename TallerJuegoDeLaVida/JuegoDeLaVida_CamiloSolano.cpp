#include <iostream> /*librería estándar de C++ para entrada/salida*/
#include <cstdlib> /*librería estándar con funciones estándar de C++ */
#include <vector> /*librería para implementar objeto tipo vector*/ 
#include <unistd.h> /*librería qué hacer de interfaz con el SO*/

using namespace std; /*importa el espacio de nombres de forma que no es necesario usar std:: en cada método importado*/

class Mapa /*declaración de la clase */
{
public: /*los métodos y atributos en public: no tienen restricciones al acceso externo */
  int fil;
  int col;
  vector<vector<int> > mapa; /*se declara un vector de vectores */
  
  Mapa(int f, int c);/*se declara constructor de la clase */
  void dibujar(); /*se declaran otros métodos */
  int analizarVecinos(int posf, int posc,int tipo);
  
  void ciclo();
};

Mapa::Mapa(int f, int c) /*se define constructor de la clase */
{
  fil = f;
  col = c;
  mapa.resize(fil); /*método de la clase vector, cambia el tamaño del el vector,a continuación se fija el tamaño de mapa 2D */
  for(int i=0; i<mapa.size(); i++)
    {
      mapa[i].resize(col);
    }
  /*a continuación se recorre y llena el mapa aleatoriamente con 0,1 o 2*/
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  mapa[f][c] = rand()%3;
        }
    }
}

void Mapa::dibujar()
/*a continuación se escribe en la terminal *,, o . en forma de rectángulo de acuerdo a el mapa definido y saltado de línea con cout << "\n"*/
{
  for(int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  if(mapa[f][c] == 0)
	    cout << ". ";
	  if(mapa[f][c] == 1)
	    cout << "* ";
    if(mapa[f][c] == 2)
      cout << "o ";

        }
      cout << "\n";
    }
}

int Mapa::analizarVecinos(int posf, int posc,int tipo)
{
/*a continuación se consideran lo 8 posibles vecinos, cada uno con dos if, uno para el verificar el límite del mapa y otro para verificar la posición vecina y si es del tipo(especie) dada, si las condiciones se cumplen se acomula un vecino y finalmente se devuelve este último valor */
  int vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == tipo)
      vecinos++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == tipo)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == tipo)
      vecinos++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == tipo)
      vecinos++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == tipo)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == tipo)
      vecinos++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == tipo)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == tipo)
      vecinos++;
  return vecinos;
}

void Mapa::ciclo()
{
/*a continuación se genera una nueva configuración, inicialmente se recorre y genera la nueva configuración para cada ubicación de acuerdo a las reglas(ej. si la ubicacion está en 0 y tiene 3 vecinos la nueva configuración es 1) */
  vector<vector<int> > nueva_conf = mapa;
  
  for (int f=0; f<fil; f++)
    {
      for(int c=0; c<col; c++)
        {
	  int n_vecinos1 = analizarVecinos(f, c,1);
    int n_vecinos2 = analizarVecinos(f, c,2);
    /*En cuanto a el conflicto de especies se eligió la regla: se calcula cual es la especie con mayor número de especímenes alrededor de la ubicación, a la especie ganadora se le aplican las reglas tradicionales de forma que la especie perdedora no es tomada en cuenta, si el número de vecinos de ambas especie es igual el estado se mantiene */

    if(n_vecinos1>n_vecinos2){

	  if(mapa[f][c] == 0){
	      if(n_vecinos1 == 3)
		      nueva_conf[f][c] = 1;
	      else
		      nueva_conf[f][c] = 0;}


	  if (mapa[f][c] == 1 || mapa[f][c] == 2){
	      if(n_vecinos1 == 2 || n_vecinos1 == 3)
		      nueva_conf[f][c] = 1;
	      else
		      nueva_conf[f][c] = 0;}
    }


    if(n_vecinos1<n_vecinos2){

      if(mapa[f][c] == 0){
        if(n_vecinos2 == 3)
          nueva_conf[f][c] = 2;
        else
          nueva_conf[f][c] = 0;}


      if (mapa[f][c] == 1 || mapa[f][c] == 2){
        if(n_vecinos2 == 2 || n_vecinos2 == 3)
          nueva_conf[f][c] = 2;
        else
          nueva_conf[f][c] = 0;}
    }

    if(n_vecinos1==n_vecinos2)
      nueva_conf[f][c]=mapa[f][c];



    }} 



  
  mapa = nueva_conf;
}

int main()
{
  srand(time(NULL));/*se genera un nueva semilla para números aleatorios*/
  Mapa mapa(50, 50); /*se crea una instancia de la clase Mapa con nombre mapa */
  while(1)
    {
      mapa.dibujar();/*se escribe en la terminal */
      usleep(100000);/*se para el proceso por 100000 microsegundos */
      system("clear");/*se limpia la terminal */
        mapa.ciclo();/*se actualiza el mapa */
    }
}

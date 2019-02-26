/* Programa hola mundo en C++ */

#include <iostream>
/*using namespace std;*/

int main(){
  std :: cout << "Hola mundo";  //"<< endl;
  return 0;
}

/* Q1: Al remover la línea aparece un error en la compilación porque cout no está declarada,
* el problema es que cout está definida en el namespace std.
* También aparece una sugerencia para arreglarlo que es escribir std::cout,  */

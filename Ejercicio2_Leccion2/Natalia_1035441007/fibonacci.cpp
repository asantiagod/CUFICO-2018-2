/* En este codigo se procesara la serie
de fibonacci un numero finito de veces, 
posteriormente se exportara a un archivo 
de texto*/

#include <iostream>
using namespace std;

int main(){
 int a, b, i, F;
  a=1;
  b=1;
  
  while(i<100){
    i+=1; // contador de uno en uno
    F=a+b; // la suma de 2 consecutivos
    a=b; // reasignar variables a los siguientes numeros
    b=F;
    if(F % 2 ==0){ //condicion para saber si es par
      cout<< F<< endl;
    }
  }
  return 0;
}

/* es posible ver como se imprimer resultados negativos,
sin embargo, esto se debe a que la variable int tiene
un limite de cifras, y al este ser superado, se pierde
la precision. esto problema se podria solucionar con long
int, sin embargo, despues de cierto numero de cifras el
problema volveria a aparecer*/


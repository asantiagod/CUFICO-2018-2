//Programa para calcular los número pares de la serie Fibonacci hasta el N que quiera el usuario

#include <iostream>
using namespace std;

int Nmax{0}; // Último número de la serie que se va a calcular
int Fn1{0}; // 1er número de la serie
int Fn2{1}; // Segundo número de la serie
int Fn3{0}; // Variable para almacenar la suma de Fn1 y Fn2
int i{0}; //Contador de la serie

int main(){
  FILE *output;

  output = fopen("Fibonacci.txt","w"); //Abre un archivo de nombre Fibonacci para escribir en él
  
  cout << "Número de términos de la suma" << endl; // Imprime el mensaje para la entrada de Nmax
  cin >> Nmax; // Entrada de Nmax por el usuario
  cout << "Números pares de Fibonacci hasta N >= "<< Nmax << endl; // Imprime una línea en blanco

  if (Nmax > 3){
  for(i = 1; i <= Nmax-2; i++){
    Fn3 = Fn2 + Fn1; // Fn+1 = Fn + Fn-1
    
    // Desplazar tanto Fn1 como Fn2 un paso a la derecha de la serie
    Fn1 = Fn2;
    Fn2 = Fn3;

    if((Fn3%2)==0){ // Escogencia de los pares     
      cout << "N = " << i+2 << "    "; // Imprime el n que le corresponde en la serie
      cout << "Fn = " << Fn3 << endl; // Imprime el valor de Fn
      fprintf(output,"N = %d  Fn = %d\n",i+2,Fn3); // Escribe en Fibonacci.txt el n y en Fn
    }
}
  }
  fclose(output); // Cierra el archivo Fibonacci
  return 0;
}

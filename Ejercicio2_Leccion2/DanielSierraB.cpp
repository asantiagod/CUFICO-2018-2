/*
*Serie de Fibinacci
*/
#include <iostream>
using namespace std;

int main() {
int i = 0;
long int a = 1;	//utilice "long int" y no "int" para obtener mas numeros pares de la serie de
long int b = 1;	//Fibonacci, ya que cuando los resultados exceden la capacidad de digitos que
long int c = 1;	//soporta el tipo de variable se empiezan a obtener nomeros negativos 
while (i<100){
a = c;
c = b + c;	//Resultado de la serie
b = a;
i++;
if (c % 2 == 0){	//se utiliza el operador mudulo % para identificar si "c" es un numero par
cout << c << endl;
}
}
return 0;
}

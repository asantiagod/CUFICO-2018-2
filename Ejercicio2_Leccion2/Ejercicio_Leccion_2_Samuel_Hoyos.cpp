#include <iostream>
#include <cstdlib>   //Se definen las librerias necesarias
#include <stdio.h>
using namespace std;

int main() 

{
int num=1;
int anterior=0;
int aux;
for (int i=0; i<50;i++){    
if (num%2==0) { //Se impone la restriccion para que solo imprima numeros pares 
printf("%d ,", num);
}
aux=num;
num += anterior;
anterior=aux;
}
return 0;
}



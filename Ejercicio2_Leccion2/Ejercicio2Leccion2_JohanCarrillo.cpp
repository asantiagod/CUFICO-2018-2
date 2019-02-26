#include<iostream>

using namespace std;

int main(){
int i_ant = 0;  //Esta variable guardara el termino anterior.
int i_sig = 1;  //Esta variable guardara el termino siguiente.
int i_sum = 1;  //Esta variable guardara la suma de los dos terminos.
int j = 0;  //Esta variable servira como contador de los terminos pares.
int n;  //Esta variable sera el numero de pares que el usuario quiere.

cout << "Ingrese el numero de pares de la sucesion de fibonacci que quiere que se impriman en pantalla." << endl;
cin >> n; //Lectura del numero de pares que el usuario desea.

while (j<n){

if (i_sum%2 == 0){  //Se evalua la condicion para saber si el termino es par.
cout << i_sum << endl;  //Si es par se imprime en pantalla.
j+=1;
}

//Se redefinen los terminos para hallar el siguiente de la sucesion.
i_ant = i_sig;
i_sig = i_sum;
i_sum = i_ant + i_sum;
}

}

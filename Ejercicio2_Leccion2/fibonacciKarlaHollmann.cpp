#include <iostream>

using namespace std;

int main() {
	int f1=0, f2=1, m=0,i=0; 

	while(i<60) {
	m=f2; //Defino m igual a f2
	f2+=f1; //sumo f1 a f2 
	if (f2% 2 == 0){cout<<f2<<endl; //si el nuevo f2 es par imprimirlo 
	}
	f1=m; //f1 va a ser ahora quien en un inicio era f2
	i+=1; //contador
	}
}

/*
creeria que los valores negativos al compilar se dan por definir las variables como int, ya que este solo toma 10 dígitos + signo, así que
podría existir un error cuando los valores tienen más de 10 dígitos 
*/

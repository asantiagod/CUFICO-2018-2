/*
Sucesion de Fibonacci
Camilo Jose Torres Casta√±o
1036401258
*/

#include <iostream> // Para realizar operaciones de entrada y salida
using namespace std;

int main () 
{ 
int f1, f2, i,fibo; //Declara las variables

f1 = 1, f2 = 1; 

for (i = 0; i < 40; i++){ //para calcular la sucesion de fibonacci
	fibo = f1+f2;
	f1=f2;
	f2 = fibo;
	
	if(fibo % 2 == 0){   //Determina si un numero es par o impar
		cout<<fibo<<endl;	
		}

	} 
} 

/*
Debido a que se declararon las variables como int (enteros), estas solo guardan 4 bytes de informaciÛn por lo que despuÈs de ciertos n˙meros de la sucesion de Fibonacci, estos exeden el n˙mero de bytes y empiezan a aparecer n˙meros negativos. Por lo que trabajar con enteros (int) tiene ciertos problemas al momento de realizar operaciones donde se tiene que guardar n˙meros muy grandes en una variable.
*/

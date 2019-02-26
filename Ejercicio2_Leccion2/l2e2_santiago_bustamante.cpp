/*Este programa muestra en pantalla los primeros
N numeros pares de Fibonacci

Santiago Bustamante

FI: 16 de Ago 2018
UM: 16 de Ago 2018
 */

#include<iostream>
using namespace std;

int main()
{
	int i = 1, j = 1, N = 50, temp = 0, l=0;
	while (l<N){
		temp = i+j;
		i = j;
		j = temp;
		//cout << temp << endl;
		if (temp%2==0){
			cout << temp << endl;
			l += 1;
		}
	}
	return 0;
}
		

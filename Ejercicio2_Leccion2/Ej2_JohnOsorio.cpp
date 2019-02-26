#include <iostream>
using namespace std;

int a = 1;
int b = 1;
int aux = 0;
int N = 20; 

int main(){
	//cout << a << endl << b << endl;
	for(int i= 0; i<N; i++)
	{
		aux = b;
		b += a;
		a = aux;

		if(b%2==0)
		{
		cout << b << endl;
		}		
	}
	return 0;
}


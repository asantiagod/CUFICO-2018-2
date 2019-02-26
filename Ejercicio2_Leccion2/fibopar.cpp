#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void escribir();

 int main(){
 	int i = 0;
 	int j = 1;
 	int f[5000];
 	f[0] = i;
 	f[1] = j;
 	for(int i=2; i<4999; i++){
 		f[i] = f[i-1] + f[i-2];
 		
 		

 		
	}
 	
 	for(int i=0; i<4998; i++){
 		if( (f[i] % 2) == 0)
 		cout << abs(f[i]) << endl; 
 	}
void escribir(){
	ofstream archivo;
	archivo.open("fibo",ios::out);



}
archivo << f[i];
archivo.close();
 }
#include <iostream>

using namespace std;

int main() {
 	double b=1.001;	
 	while (b<10000){
 	b*=1.001;
 	cout << b <<endl;
  	}	
	return 0;
}

/*
*real	0m0.029s
user	0m0.017s
sys	0m0.012s
*/


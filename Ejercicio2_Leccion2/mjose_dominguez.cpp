/*
 * Ejercicio 2 de la leccion 2
 */
#include <iostream>
using namespace std;
int main() {
	int f0 = 0, f1 = 1, fn;
	for (int i=0; i<100000; i++) {
		if (fn % 2 ==0) {
			cout << fn <<endl;
		}
		fn = f0 + f1;
		f0 = f1;
		f1 = fn;
		}
	return 0;
	}

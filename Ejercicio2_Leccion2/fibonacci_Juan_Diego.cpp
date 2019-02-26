#include <iostream>

using namespace std;

int main(){
int num1 = 0, num2 = 1, i, dummy;

for(i =0 ; i<40; i++){

	dummy = num1 + num2;
	num1 = num2;
	num2 = dummy;
	
	if( dummy%2 == 0){
	cout << dummy << endl;

	}	



	}


}

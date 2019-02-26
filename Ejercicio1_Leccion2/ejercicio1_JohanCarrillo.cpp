#include<iostream>
#include <ctime> 

using namespace std;

int main(){

unsigned t0, t1;
 
t0=clock();
double b = 1.001;
while (b<10000){

b*=1.001;
cout << b << endl;
}

t1 = clock();


double time = (double(t1-t0)/CLOCKS_PER_SEC);
cout << "Execution Time: " << time << endl;

}

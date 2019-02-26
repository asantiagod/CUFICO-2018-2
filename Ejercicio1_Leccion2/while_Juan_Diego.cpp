#include <iostream>

using namespace std;

int main(){


double b = 1.001;
while (b<1000){

b*=1.001;
cout << b << endl;
}

// real	0m0.052s
//user	0m0.012s
//sys	0m0.026s

}


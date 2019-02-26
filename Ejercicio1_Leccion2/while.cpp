#include <iostream>
#include <time.h> 
 


double b = 1.001;
using namespace std;
int main()
{
while (b<10000)
{
b*=1.001;
cout << b << endl;
}

}


#include <iostream>

using namespace std;


int main()
{
    float d = 1.001;
    while (d<10000)
        {
            d *= 1.001;

            cout <<  d << endl;

        }    
  
  return 0;
}

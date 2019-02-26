#include <iostream>

using namespace std;


int main()
{
    int Niter = 50;
    long long int F = 1;
    for (int i = 0; i < Niter; i++)
    {
        F += F;

        if (F%2==0)
        {
            cout << F << endl;
        }
    }
  
  return 0;
}

/*
Leccion 2 Santiago Bustamante

FI: 16 Ago 2018
UM: 16 Ago 2018
 */

#include<iostream>

using namespace std;

int main()
{
  double b = 1.001;
  while (b<10000)
  {
    b *= 1.001;
    cout << b << endl;
  }
  return 0;
}

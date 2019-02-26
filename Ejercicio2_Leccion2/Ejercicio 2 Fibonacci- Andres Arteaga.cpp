#include<iostream>
using namespace std;
int main() {
  long x=0;
  long b=1;
  for (int i=0;i<=60;i++){
    long a;
    a=b+x;
    x=b;
    b=a;
    if (x%2==0){
      cout << x<<'\n';
    }
  }
  return 0;
}

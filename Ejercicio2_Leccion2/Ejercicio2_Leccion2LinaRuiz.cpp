#include <iostream>
using namespace std;


int main(){
    int a=0;
    int b=1;
    cout<<a<<endl;
    for(int i=1;i<=22;i++){
       a=a+b;
       b=b+a;
       if(a%2==0){
         cout<<a<<endl;
       }
       if(b%2==0){
         cout<<b<<endl;
       }
     }

     return 0;
}

#include <iostream>   

using namespace std;

int main() {               
   int a=1;
   int b=1;
   int max=1000000;
    
    while (b<max){
        
        int s=a+b;
        if(s%2==0){
            cout << s << endl;}
        a=b;
        b=s;
        
    
    }
 
    return 0;

                        
} 

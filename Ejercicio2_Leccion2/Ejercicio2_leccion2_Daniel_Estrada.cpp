#include<iostream>

using namespace std;

int main()
{
    int a_1 = 1, a_2 = 1, a_n;
    
    cout << a_1 << endl;
    cout << a_2 << endl;

    for(int i;i<=43;i++)
    {
        a_n = a_1 + a_2;
        
        cout << a_n << endl;
        
        a_1 = a_2;
        a_2 = a_n;
        
    }
    cout << ".\n.\n." << endl;

    return 0;
}

/**
 * @author Andrés Santiago Duque 
 */
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	char fName[] = "Fibonacci.txt";
	unsigned long long fb[2] = {0,1};
	ofstream file(fName);
	
	for(int i=0; i<100; ++i)
	{
		unsigned long long temp;
		temp = fb[1];
		fb[1] += fb[0];
		fb[0] = temp;
		
		if(fb[0] > fb[1]) //¿Se desbordar?
			break;
		
		if(temp%2 == 0)
			file<<temp<<endl;
	}
	file.close();
}
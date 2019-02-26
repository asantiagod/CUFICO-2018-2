#include <iostream>

int main(){
    float b = 1.001;

    while(b < 1000) {
        b *= 1.001;
        std::cout << b << std::endl;
    }

    return 0;
}
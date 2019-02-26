#include <iostream>


int main(){
    int a = 12;
    int b = 13;

    if (a <= 30){
        std::cout << 5 * a << std::endl;
    }

    if (a <= 30 && b > 30){
        std::cout << "Both conditions satisfied" << std::endl;
    }else{
        std::cout << "No condition satisfied" << std::endl;
    }

    float c = 12.53;

    if (c <= 2){
        std::cout << "First condition satisfied" << std::endl;
    }else if (a <= 6 && a > 2){
        std::cout << "Second condition satisfied" << std::endl;
    }else if (a <= 13 && a > 6){
        std::cout << "Third condition satisfied" << std::endl;
    }

    double d = 0.001;

    while(d < 10000){
        d *= 1.001;
        std::cout << d << std::endl;
    }


    return 0;
}
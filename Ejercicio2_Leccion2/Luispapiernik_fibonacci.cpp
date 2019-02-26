#include <iostream>


int main(){
    int fi = 1, ff = 1, temp = 1;
    for (int i = 1; i < 30; ++i){
        if (ff % 2 == 0)
            std::cout << ff << std::endl;
        temp = fi + ff;
        fi = ff;
        ff = temp;
    }

    return 0;
}
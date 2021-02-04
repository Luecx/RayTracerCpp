#include <iostream>
#include <chrono>
#include <iomanip>
#include "vector.h"

int main() {

    vector v1{26};
    vector v2{26};

    v1[2] = 3;
    v1[1] = 3;
    v2[1] = 43;

    vector v3 = v2 + v1;
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1e9; i++){
        v3 *= 1.0001;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << std::left << std::setw(20) << elapsed.count() << std::endl;


}

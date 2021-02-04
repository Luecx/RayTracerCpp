#include <iostream>
#include <chrono>
#include <iomanip>
#include "Vector.h"
#include "types.h"
#include "intersect.h"

int main() {

//    Vector v1{3};
//    Vector v2{3};
//
//
//    for(int i = 0; i< 3; i++){
//        v1[i] = i;
//        v2[i] = 3- 2 * i;
//    }
//
//    Vector v3 = v2 + v1;
//    std::cout << v1 << std::endl;
//    std::cout << v2 << std::endl;
//    std::cout << v3 << std::endl;

//    Vector v1{1,1,1};
//    Vector v2{3};
//    v2 = -v1;

    Plane p{{0,0,0},{0,1,0}};
    Ray   r{{1,1,1},{0,-1,0}};
    std::cout << intersect_ray_plane(r, p) << std::endl;




}

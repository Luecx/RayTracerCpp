#include <iostream>
#include <chrono>
#include <iomanip>
#include "Vector.h"
#include "types.h"
#include "intersect.h"
#include "file_io.h"
#include <time.h>

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

//    Plane p{{0,0,0},{0,1,0}};
//    Ray   r{{1,1,1},{0,-1,0}};
//    std::cout << intersect_ray_plane(r, p) << std::endl;
//
//
//    std::cout << r.base + (r.direction * 1) << std::endl;

//    Triangle t{{1,1,0},{-1,0,0},{1,-1,1}};
//    Plane p{{0,0,0},{0,1,0}};
//    Ray intersection = intersect_triangle_plane(t, p);
//    std::cout << intersection.base << std::endl;
//    std::cout << intersection.direction << std::endl;

//    AABB aabb{{0,0,0}, {1,1,1}};
//    Ray  r{{0.5,3,0.5},{0.1,-0.89,0}};

//    std::cout << intersect_ray_aabb(r, aabb);


    double time = 0.0;

    double start = clock();

    readFile("../Test.obj");

    time += clock() - start;

    time = time / CLOCKS_PER_SEC;
    std::cout << "Time need for readOBJ " << time << " sec." << std::endl;
}

#include <iostream>
#include <chrono>
#include <iomanip>
#include "Vector.h"
#include "types.h"
#include "intersect.h"
#include "file_io.h"
#include "Image.h"
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

//    Triangle t{{0,0,1},{-1,0,1},{-1,-1,1}};
//    Plane p{{0,0,0},{0,1,0}};
//    Ray r = intersect_triangle_plane(t, p);
//    std::cout << r.base << " " << r.direction;

//    Ray   r{{1,1,1},{0,-1,0}};
//    std::cout << intersect_ray_plane(r, p) << std::endl;
//
//
//    std::cout << r.base + (r.direction * 1) << std::endl;


//    Ray intersection = intersect_triangle_plane(t, p);
//    std::cout << intersection.base << std::endl;
//    std::cout << intersection.direction << std::endl;

//    AABB aabb{{0,0,0}, {1,1,1}};
//    Ray  r{{0.5,3,0.5},{0.1,-0.89,0}};

//    std::cout << intersect_ray_aabb(r, aabb);


//    double start = clock();
//
    std::vector<Triangle> triangles = readFile("../res/cube.obj");

    KdTree kdNode{triangles, 4, 0};


//    std::cout << "Time need for readOBJ " << ((clock() - start) / CLOCKS_PER_SEC) << " sec." << std::endl;


    KdNode kdNode{aabb, triangles, 1};
    std::cout << "Time need for readOBJ " << (clock() - start) << "ms." << std::endl;

    Image m(500, 500);

    for (int x = 0; x < 500; x++) {
        for (int y = 0; y < 500; y++) {
            m.setPixel(x, y, Pixel(x % 255, y % 255, y * x % 255));
        }
    }

    m.write("HelloThere.ppm");

}

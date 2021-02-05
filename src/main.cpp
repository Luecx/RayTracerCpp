#include <iostream>
#include <chrono>
#include <iomanip>
#include "Vector.h"
#include "types.h"
#include "intersect.h"
#include "file_io.h"
#include "Image.h"
#include <time.h>
#include <cmath>

int main() {

//    std::vector<Triangle> triangles = readFile("../res/bunny.obj");
//    std::cout << "creating kd tree" << std::endl;
//    KdTree kdNode{triangles, 10, 2};
//    std::cout << "creating kd tree finished" << std::endl;


//    Image m(1000,1000);
////#pragma omp parallel for schedule(static) num_threads(24)
//    auto start = clock();
//    for(int i = 0; i < 1000; i++){
//        std::cout <<"\rprogress: "<<  (i+1) * 100.0 / 1000.0 << " %" << "time: " << clock() - start / 1000.0 << "s" << std::flush;
//            for(int j = 0; j < 1000; j++){
//            Ray r {{-0.1 + i / 5000.0, 0.2 - j / 5000.0, 0.4},{0,0,-1}};
//            double d = intersect_ray_kdtree(r, kdNode);
//            if(d < INFTY){
//                Pixel p{(int)(255 * std::min(d/5,1.0)),(int)(255 * std::min(d/5,1.0)),(int)(255  * std::min(d/5,1.0))};
//                m.setPixel(i,j,p);
//            }
//        }
//    }
//    m.write("HelloThere1.ppm");

    auto start = clock();
    AABB aabb{{-1,-1,-1}, {1,1,1}};
    Triangle t {{-0.1 + 0 / 5000.0, 0.2 - 0 / 5000.0, 0.4},{0,0,-1}, {3,2,1}};
    Ray r {{-0.1 + 10 / 5000.0, 3 - 0 / 5000.0, 0.4},{0,0,-1}};


    double a = 0;
    for(int i = 0; i < 10000000; i++){
        a += intersect_ray_triangle(r, t);
    }
    std::cout << a << std::endl;
    std::cout << clock() - start << std::endl;

//    std::cout << "Time need for readOBJ " << ((clock() - start) / CLOCKS_PER_SEC) << " sec." << std::endl;


//    KdNode kdNode{aabb, triangles, 1};
//    std::cout << "Time need for readOBJ " << (clock() - start) << "ms." << std::endl;
//
//    Image m(500, 500);
//
//    for (int x = 0; x < 500; x++) {
//        for (int y = 0; y < 500; y++) {
//            m.setPixel(x, y, Pixel(x % 255, y % 255, y * x % 255));
//        }
//    }

//    m.write("HelloThere.ppm");

}

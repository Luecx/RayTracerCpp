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

    std::vector<Triangle> triangles = readFile("../res/bunny.obj");
    std::cout << "creating kd tree" << std::endl;
    KdTree kdNode{triangles, 4, 0};
    std::cout << "creating kd tree finished" << std::endl;

//    Triangle t {{-1,-1,0},{1,1,0},{1,-1,0}};
//    Ray r{{0.5,-0.5,10},{0,0,-1}};





    Image m(100, 100);

//    for(int i = 0; i < 100; i++){
//        for(int j = 0; j < 100; j++){
//            Ray r {{-0.1 + i / 400.0, 0.25 - j / 400.0, 1},{0,0,-1}};
//            double d = intersect_ray_kdtree(r, kdNode);
//
//
//            double d = intersect_ray_triangle(r, t);
//            for(Triangle& t:triangles){
//                d = std::min(d,intersect_ray_triangle(r, triangles[2]) );
//            }
//
//            if(std::isfinite(d)){
//                std::cout << i << " " << j << std::endl;
//                Pixel p{(int)(255 * std::min(d,1.0)),(int)(255 * std::min(d,1.0)),(int)(255  * std::min(d,1.0))};
//                m.setPixel(i,j,p);
//            }
//        }
//    }

    m.write("HelloThere.bmp");

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

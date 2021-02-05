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
    KdTree kdNode{triangles, 10, 2};

    Image m(1000,1000);
    auto start = clock();
#pragma omp parallel for schedule(static) num_threads(24)
    for(int i = 0; i < 1000; i++){
        std::cout <<"\rprogress: "<<  (i+1) * 100.0 / 1000.0 << " %" << "time: " << clock() - start / 1000.0 << "ms" << std::flush;
            for(int j = 0; j < 1000; j++){
            Ray r {{-0.1 + i / 5000.0, 0.2 - j / 5000.0, 0.4},{0,0,-1}};
            TriangleCoordinate t{};
            double d = intersect_ray_kdtree(r, kdNode,t);
            if(d < INFTY){

                Pixel p{(int)(255 * t.w), (int)(255 * t.u), (int)(255 * t.v)};
                m.setPixel(i,j,p);
            }
        }
    }
    m.write("HelloThere1.ppm");

}

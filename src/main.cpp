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
#include "scene.h"
#include "render.h"

int main() {

    Config      config{};
    Scene       scene{};
    Renderer    renderer{};

    Light  l1{{1,2,3}, 1};
    scene.addLight(l1);

    Camera c1{{-1,0,0}, {1,0,0}, {0,0,1}};
    scene.setCamera(c1);
//
    std::vector<Triangle> triangles = readFile("../res/bunny.obj");
    scene.addModel(triangles, config);

    Image o = renderer.render(scene, config);
    o.write("temp2.ppm");


//    KdTree kdNode{triangles, 3, 2};
//
//    Image m(1000,1000);
//    int progress = 0;
//    auto start = clock();
//#pragma omp parallel for schedule(static) num_threads(24)
//    for(int i = 0; i < 1000; i++){
//
//        for(int j = 0; j < 1000; j++){
//            Ray r {{-2 + i / 250.0, 2 - j / 250.0, 3.4},{0,0,-1}};
//            HitData t{};
//            double d = intersect_ray_kdtree(r, kdNode,t);
//
//            Vector norm = t.triangle.getNormal(t.coordinate);
//            norm *= (1 / norm.mag());
//
//            if(d < INFTY){
//
//                Pixel p{
//                    (int)(127 * (1 + norm[0])),
//                    (int)(127 * (1 + norm[1])),
//                    (int)(127 * (1 + norm[2]))};
////                Pixel p {
////                        (int)(255 * t.coordinate.w),
////                        (int)(255 * t.coordinate.u),
////                        (int)(255 * t.coordinate.v),
////                };
//                m.setPixel(i,j,p);
//            }
//        }
//        std::cout   <<"\r"
//                    << "progress: " <<  (++progress) * 100.0 / 1000.0       << " %   "
//                    << "time: "     <<  (clock() - start) / 1000.0          << " s   "
//                    << std::flush;
//    }
//    m.write("HelloThere1.ppm");

}

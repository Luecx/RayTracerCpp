//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_INTERSECT_H
#define RAYTRACER_INTERSECT_H

#include "types.h"
#include "Triangle.h"
#include "KdTree.h"

#define EPSILON  1e-27
#define INFTY 1e18


struct HitData{
    Triangle            triangle;
    TriangleCoordinate  coordinate;
    double              distance = INFTY;
};

double intersect_ray_triangle     (Ray &r, Triangle &t, TriangleCoordinate& coordinate);
double intersect_ray_plane        (Ray &r, Plane &p);
Ray    intersect_triangle_plane   (Triangle &t, Plane &p);
double intersect_ray_aabb         (Ray &r, AABB& aabb);
double intersect_ray_kdtree       (Ray &r, KdTree &tree, HitData& coordinate);

#endif //RAYTRACER_INTERSECT_H

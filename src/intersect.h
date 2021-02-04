//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_INTERSECT_H
#define RAYTRACER_INTERSECT_H

#include "types.h"
#include "Triangle.h"
#include "KdTree.h"

#define EPSILON 1e-10


double intersect_ray_triangle     (Ray &r, Triangle &t);
double intersect_ray_plane        (Ray &r, Plane &p);
Ray    intersect_triangle_plane   (Triangle &t, Plane &p);
double intersect_ray_aabb         (Ray &r, AABB& aabb);
double intersect_ray_kdtree       (Ray &r, KdTree &tree);

#endif //RAYTRACER_INTERSECT_H

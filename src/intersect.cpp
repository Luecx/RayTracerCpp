//
// Created by Luecx on 04.02.2021.
//

#include "intersect.h"
#include "types.h"

double intersect_ray_plane(Ray &r, Plane &p) {
    double denom = p.normal * r.direction;
    return (p.base - r.base) * p.normal / denom;
}


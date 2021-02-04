//
// Created by Luecx on 04.02.2021.
//

#include <iostream>
#include "intersect.h"
#include "types.h"

double intersect_ray_plane(Ray &r, Plane &p) {
    double denom = p.normal * r.direction;
    std::cout << p.normal << std::endl;
    std::cout << r.direction << std::endl;
    std::cout << p.base - r.base << std::endl;
    std::cout << denom << std::endl;
    return (p.base - r.base) * p.normal / denom;
}


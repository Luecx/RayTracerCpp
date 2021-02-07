//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Vector.h"

struct Plane {
    Vector base{};
    Vector normal{};
};

struct Ray {
    Vector base{};
    Vector direction{};
};

struct AABB {
    Vector min{};
    Vector max{};
};

struct Light {
    Vector position{};
    double radius = 0;
};

struct Camera {
    Vector position{};
    Vector direction{};
    Vector up{};
};

#endif //RAYTRACER_PLANE_H

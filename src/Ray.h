//
// Created by ICH on 04-Feb-21.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vector.h"

class Ray {
private:
    Vector base{3};
    Vector direction{3};

public:
    Ray(const Vector &base, const Vector &direction);
};


#endif //RAYTRACER_RAY_H

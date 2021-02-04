//
// Created by Luecx on 04.02.2021.
//

#ifndef RAYTRACER_INTERSECT_H
#define RAYTRACER_INTERSECT_H

double intersect_ray_triangle(Ray &r, Triangle &t);
double intersect_ray_plane   (Ray &r, Plane &p);

#endif //RAYTRACER_INTERSECT_H

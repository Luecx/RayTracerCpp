//
// Created by Luecx on 04.02.2021.
//

#include <iostream>
#include "intersect.h"
#include "types.h"
#include <cmath>

Ray intersect_triangle_plane(Triangle &t, Plane &p) {

    Vector p1{};
    Vector p2{};
    bool foundFirst = false;

    Vector r1{}, r2{}, r3{};

    double s1 = (t[0]-p.base)*p.normal;
    double s2 = (t[1]-p.base)*p.normal;
    double s3 = (t[2]-p.base)*p.normal;

    // check if any points lie directly in the plane. If two lay on the plane, we consider it as NO intersection!
    if(std::abs(s1) <= EPSILON || std::abs(s2) <= EPSILON || std::abs(s3) <= EPSILON ){
        if(std::abs(s1) <= EPSILON){
            p1 = t[0];
            foundFirst = true;
        }
        if(std::abs(s2) <= EPSILON){
            if(foundFirst){
                p2 = t[1];
                return {p1, p2};
            }else{
                p1 = t[1];
                foundFirst = true;
            }
        }
        if(std::abs(s3) <= EPSILON ){
            if(foundFirst){
                p2 = t[2];
                return {p1, p2};
            }else{
                p1 = t[2];
                foundFirst = true;
            }
        }
    }
    // if we have not found at least one point and all lie on the same side of the plane, return
    if(s1 > 0 && s2 > 0 && s3 > 0 && !foundFirst){
        return {};
    }
    if(s1 < 0 && s2 < 0 && s3 < 0 && !foundFirst){
        return {};
    }

    for(int i = 0; i < 3; i++){
        Ray temp{t[i], t[(i+1)%3] - t[i]};
        double r = intersect_ray_plane(temp, p);
        if(std::isfinite(r) && r > EPSILON && r < (1-EPSILON)){
            if(foundFirst){
                p2 = temp.base + temp.direction * r;
                return {p1,p2-p1};
            }else{
                p1 = temp.base + temp.direction * r;
                foundFirst = true;
            }
        }
    }

    return {};
}

double intersect_ray_plane(Ray &r, Plane &p) {
    double denom = p.normal * r.direction;
    if(std::abs(denom) <EPSILON){
        return 1.0 / 0.0;
    }
    double numer = p.normal * (p.base - r.base);
    return numer / denom;
}

double intersect_ray_aabb(Ray &r, AABB &aabb) {
    double tmin, tmax, tymin, tymax, tzmin, tzmax;

    Vector bounds[]{aabb.min, aabb.max};
    bool   sign  []{1.0/r.direction[0] < 0, 1.0/r.direction[1] < 0, 1.0/r.direction[2] < 0};

    tmin =  (bounds[  sign[0]][0] - r.base[0])      / r.direction[0];
    tmax =  (bounds[1-sign[0]][0] - r.base[0])      / r.direction[0];
    tymin = (bounds[  sign[1]][1] - r.base[1])      / r.direction[1];
    tymax = (bounds[1-sign[1]][1] - r.base[1])      / r.direction[1];

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[  sign[2]][2] - r.base[2]) / r.direction[2];
    tzmax = (bounds[1-sign[2]][2] - r.base[2]) / r.direction[2];

    if ((tmin > tzmax) || (tzmin > tmax))
        return 1.0 / 0.0;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    if (tmin < EPSILON)
        return 1.0 / 0.0;

    return tmin;
}

double intersect_ray_kdtree(Ray &r, KdTree &tree) {
    if(!tree.triangles.empty()){
        double minDist =  1.0 / 0.0;
        for(Triangle& tri:tree.triangles){
            minDist = std::min(minDist, intersect_ray_triangle(r, tri));
        }
        return minDist;
    }else{
        KdTree* left  = tree.left;
        KdTree* right = tree.right;

        // check which one to search first
        double dLeft  = intersect_ray_aabb(r, left->boundingBox);
        double dRight = intersect_ray_aabb(r, left->boundingBox);

        // search left node first
        if(dLeft < dRight){
            double dist = intersect_ray_kdtree(r, *left);
            if(std::isfinite(dist)){
                return dist;
            }
        }else{
            double dist = intersect_ray_kdtree(r, *right);
            if(std::isfinite(dist)){
                return dist;
            }
        }
    }
    return 1.0 / 0.0;
}

double intersect_ray_triangle(Ray &r, Triangle &t) {

    double a,f,u,v;
    Vector edge1 = t[1] - t[0];
    Vector edge2 = t[2] - t[0];
    Vector h = r.direction.cross(edge2);
    a = edge1 * h;
    if (a > -EPSILON && a < EPSILON)
        return 1.0 / 0.0;    // This ray is parallel to this triangle.
    f = 1.0/a;
    Vector s = r.base - t[0];
    u = s * h * f;
    if (u < 0.0 || u > 1.0)
        return 1.0 / 0.0;
    Vector q = s.cross(edge1);
    v = r.direction * q * f;
    if (v < 0.0 || u + v > 1.0)
        return 1.0 / 0.0;
    // At this stage we can compute t to find out where the intersection point is on the line.
    double dist = edge2 * q * f;
    if (dist > EPSILON) // ray intersection
    {
        return dist;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return 1.0 / 0.0;
}


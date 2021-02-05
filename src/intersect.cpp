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
        if(abs(r) < INFTY && r > EPSILON && r < (1 - EPSILON)){
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
        return INFTY;
    }
    double numer = p.normal * (p.base - r.base);
    return numer / denom;
}

double intersect_ray_aabb(Ray &r, AABB &aabb) {

    double t1 = (aabb.min[0] - r.base[0]) / r.direction[0];
    double t2 = (aabb.max[0] - r.base[0]) / r.direction[0];
    double t3 = (aabb.min[1] - r.base[1]) / r.direction[1];
    double t4 = (aabb.max[1] - r.base[1]) / r.direction[1];
    double t5 = (aabb.min[2] - r.base[2]) / r.direction[2];
    double t6 = (aabb.max[2] - r.base[2]) / r.direction[2];

    double tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    double tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        return INFTY;
    }

// if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        return INFTY;
    }

    return tmin;
}

double intersect_ray_kdtree(Ray &r, KdTree &tree) {
    if(!tree.triangles.empty() || tree.left == nullptr || tree.right == nullptr){
        double minDist =  INFTY;
        for(Triangle& tri:tree.triangles){
            minDist = std::min(minDist, intersect_ray_triangle(r, tri));
        }
        return minDist;
    }else{
        KdTree* left  = tree.left;
        KdTree* right = tree.right;

        // check which one to search first
        double dLeft  = intersect_ray_aabb(r, left ->boundingBox);
        double dRight = intersect_ray_aabb(r, right->boundingBox);


        if(dLeft == INFTY && dRight == INFTY) return INFTY;
        // search left node first
        if(dLeft < dRight){
            double dist = intersect_ray_kdtree(r, *left);
            if(std::abs(dist) < INFTY){
                return dist;
            }else{
                return intersect_ray_kdtree(r, *right);
            }
        }else{
            double dist = intersect_ray_kdtree(r, *right);
            if(std::abs(dist) < INFTY){
                return dist;
            }else{
                return intersect_ray_kdtree(r, *left);
            }
        }
    }
}

double intersect_ray_triangle(Ray &r, Triangle &t) {

    double a,f,u,v;
    Vector edge1 = t[1] - t[0];
    Vector edge2 = t[2] - t[0];
    Vector h{r.direction.cross(edge2)};
    a = edge1 * h;
    if (a > -EPSILON && a < EPSILON)
        return INFTY;    // This ray is parallel to this triangle.
    f = 1.0/a;
    Vector s = r.base - t[0];
    u = s * h * f;
    if (u < 0.0 || u > 1.0)
        return INFTY;
    Vector q = s.cross(edge1);
    v = r.direction * q * f;
    if (v < 0.0 || u + v > 1.0)
        return INFTY;
    // At this stage we can compute t to find out where the intersection point is on the line.
    double dist = edge2 * q * f;
    if (dist > EPSILON) // ray intersection
    {
        return dist;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return INFTY;
}


//
// Created by QuantumRange on 04-Feb-21.
//

#include "Triangle.h"
#include "intersect.h"

Triangle::Triangle() {}

Triangle::Triangle(const Vector &&a, const Vector &&b, const Vector &&c) {
    this->points[0] = a;
    this->points[1] = b;
    this->points[2] = c;
}

Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c) {
    this->points[0] = a;
    this->points[1] = b;
    this->points[2] = c;
}

Triangle::Triangle(const Vector *points) {
    this->points[0] = points[0];
    this->points[1] = points[1];
    this->points[2] = points[2];
}

Triangle::Triangle(const Triangle &other) {
    this->points[0] = other[0];
    this->points[1] = other[1];
    this->points[2] = other[2];
}

Triangle::Triangle(Triangle &&other) {
    this->points[0] = other[0];
    this->points[1] = other[1];
    this->points[2] = other[2];
}

Triangle &Triangle::operator=(const Triangle &other){
    this->points[0] = other[0];
    this->points[1] = other[1];
    this->points[2] = other[2];
    return *this;
}

Triangle::~Triangle() {

}

const Vector &Triangle::getA() {
    return points[0];
}

const Vector &Triangle::getB() {
    return points[1];
}

const Vector &Triangle::getC() {
    return points[2];
}


Vector Triangle::center() const{
    return (points[0] + points[1] + points[2]) * (1/3.0);
}


void Triangle::splitTriangle(Plane &p, std::vector<Triangle> &lhs, std::vector<Triangle> &rhs, double originalSide) {

    Ray intersection = intersect_triangle_plane(*this, p);

    // check if its split by the plane
    if(intersection.direction.mag_squared() <= EPSILON){
        return;
    }

    // count the amount of nodes cut. if we cut more than 1 node, we will not cut the triangle at all
    bool help = false;
    for(int i = 0; i < 3; i++){
        if((this->points[i] - intersection.base).mag_squared() <= EPSILON){
            if(!help){
                help = true;
            }else{
                return;
            }
        }
    }
    // determine if a node is cut or not. if so we can split into two triangles, if not we need 3.
    for(int i = 0; i < 3; i++){
        if((this->points[i] - intersection.base).mag_squared() <= EPSILON){
            Vector p1 = intersection.base;
            Vector p2 = intersection.base + intersection.direction;

            Vector v1 = this->points[(i+1)%3];
            Vector v2 = this->points[(i+2)%3];

            Triangle t1 = {p1,p2,v1};
            Triangle t2 = {p2,p1,v2};

            if(((t1.center()-p.base) * p.normal) >= 0){
                // t1 on positive side, t2 on negative side
                if(originalSide > 0){
                    // original triangle on positive side
                    (*this) = t1;
                    lhs.emplace_back(t2);
                }else{
                    // original triangle on negative side
                    (*this) = t2;
                    rhs.emplace_back(t1);
                }
            }else{
                // t2 on positive side, t1 on negative side
                if(originalSide > 0){
                    // original triangle on positive side
                    (*this) = t2;
                    lhs.emplace_back(t1);
                }else{
                    // original triangle on negative side
                    (*this) = t1;
                    rhs.emplace_back(t2);

                }
            }
            return;
        }
    }

    // if no vertex was laying on an edge, we need to compute the new triangles.
    // For this purpose, we need to figure out which edges are intersected.
    // we check which node is being cut off.
    Ray r1 {points[0], points[1]-points[0]};  // connection p0-p1
    Ray r2 {points[1], points[2]-points[1]};  // connection p1-p2
    Ray r3 {points[2], points[0]-points[2]};  // connection p0-p2
    double c1 = intersect_ray_plane(r1, p);
    double c2 = intersect_ray_plane(r2, p);
    double c3 = intersect_ray_plane(r3, p);

    Vector cutoff;
    Vector v1;
    Vector v2;

    Vector cut1 = intersection.base;
    Vector cut2 = intersection.base + intersection.direction;

    // B is cutoff
    if(c1 > 0 && c1 < 1 && c2 > 0 && c2 < 1){
        cutoff  = this->getB();
        v1      = this->getA();
        v2      = this->getC();
    }
    // A is cutoff
    else if(c1 > 0 && c1 < 1 && c3 > 0 && c3 < 1){
        cutoff  = this->getA();
        v1      = this->getB();
        v2      = this->getC();
    }
    // C is cutoff
    else if(c2 > 0 && c2 < 1 && c3 > 0 && c3 < 1){
        cutoff  = this->getC();
        v1      = this->getA();
        v2      = this->getB();
    }
    else{
        exit(-1);
    }

    // make sure the quad has a positive jacobian
    if((v2-cut2).mag() + (v1-cut1).mag() > (v1-cut2).mag() + (v2-cut1).mag()){
        Vector h = cut1;
        cut1 = cut2;
        cut2 = h;
    }

    Triangle triC{cut1, cut2, cutoff};
    Triangle tri1{cut1, cut2, v1};
    Triangle tri2{  v1, cut2, v2};

    // check if the node which has been cut is on the positive side of the plane (positive normal direction)
    if(((cutoff-p.base) * p.normal) >= 0){
        // triC is on the positive side
        if(originalSide > 0){
            // original triangle on positive side
            (*this) = triC;
            lhs.emplace_back(tri1);
            lhs.emplace_back(tri2);
        }else if(originalSide < 0){
            // original triangle on negative side
            (*this) = tri1;
            lhs.emplace_back(tri2);
            rhs.emplace_back(triC);
        }
    }else{
        // triC is on the negative side
        if(originalSide > 0){
            // original triangle on positive side
            (*this) = tri1;
            rhs.emplace_back(tri2);
            lhs.emplace_back(triC);
        }else if(originalSide < 0){
            // original triangle on negative side
            (*this) = triC;
            rhs.emplace_back(tri1);
            rhs.emplace_back(tri2);
        }
    }

}

Triangle &Triangle::operator*=(double scale) {
    return operator*(scale);
}

Triangle &Triangle::operator*(double scale) {
    points[0] *= scale;
    points[1] *= scale;
    points[2] *= scale;
    return *this;
}



std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
    os << "A: " << triangle.points[0] << ", B: " << triangle.points[1] << ", C: " << triangle.points[2];
    return os;
}

bool Triangle::operator==(const Triangle &rhs) const {
    return points == rhs.points;
}

bool Triangle::operator!=(const Triangle &rhs) const {
    return !(rhs == *this);
}

const Vector *Triangle::getPoints() const {
    return points;
}


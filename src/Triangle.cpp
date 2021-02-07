//
// Created by QuantumRange on 04-Feb-21.
//

#include "Triangle.h"
#include "intersect.h"

Triangle:: Triangle() {}
Triangle:: Triangle(const TriangleNode &&a, const TriangleNode &&b, const TriangleNode &&c) {
    this->nodes[0] = a;
    this->nodes[1] = b;
    this->nodes[2] = c;
}
Triangle:: Triangle(const TriangleNode &a, const TriangleNode &b, const TriangleNode &c) {
    this->nodes[0] = a;
    this->nodes[1] = b;
    this->nodes[2] = c;
}
Triangle:: Triangle(const Triangle &other) {
    this->nodes[0] = other[0];
    this->nodes[1] = other[1];
    this->nodes[2] = other[2];
}
Triangle:: Triangle(Triangle &&other) {
    this->nodes[0] = other[0];
    this->nodes[1] = other[1];
    this->nodes[2] = other[2];
}
Triangle::~Triangle() {

}
Triangle &Triangle::operator=(const Triangle &other){
    this->nodes[0] = other[0];
    this->nodes[1] = other[1];
    this->nodes[2] = other[2];
    return *this;
}

const TriangleNode &    Triangle::getA() {
    return nodes[0];
}
const TriangleNode &    Triangle::getB() {
    return nodes[1];
}
const TriangleNode &    Triangle::getC() {
    return nodes[2];
}

Vector                  Triangle::center() const{
    return (nodes[0].position + nodes[1].position + nodes[2].position) * (1/3.0);
}
std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
    os << "A: " << triangle.nodes[0] << ", B: " << triangle.nodes[1] << ", C: " << triangle.nodes[2];
    return os;
}

Triangle&   Triangle::operator*=(double scale) {
    return operator*(scale);
}
Triangle&   Triangle::operator* (double scale) {
    nodes[0].position *= scale;
    nodes[1].position *= scale;
    nodes[2].position *= scale;
    return *this;
}
bool        Triangle::operator==(const Triangle &rhs) const {
    return nodes == rhs.nodes;
}
bool        Triangle::operator!=(const Triangle &rhs) const {
    return !(rhs == *this);
}

TriangleCoordinate  Triangle::barycentric(Vector &vec){
    Vector v0 = getB().position - getA().position, v1 = getC().position - getA().position, v2 = vec - getA().position;
    double d00 = v0 * v0;
    double d01 = v0 * v1;
    double d11 = v1 * v1;
    double d20 = v2 * v0;
    double d21 = v2 * v1;
    double denom = d00 * d11 - d01 * d01;
    double u = (d11 * d20 - d01 * d21) / denom;
    double v = (d00 * d21 - d01 * d20) / denom;
    double w = 1.0 - u - v;

    return TriangleCoordinate{u,v,w};
}
Vector              Triangle::getNormal         (TriangleCoordinate &coordinate){
    return nodes[0].normal * coordinate.w +
           nodes[1].normal * coordinate.u +
           nodes[2].normal * coordinate.v;
}
Vector              Triangle::getPosition       (TriangleCoordinate &coordinate){
    return nodes[0].position * coordinate.w +
           nodes[1].position * coordinate.u +
           nodes[2].position * coordinate.v;
}
TriangleNode        Triangle::createNode        (TriangleCoordinate &coordinate){
    return {
            getPosition(coordinate),
            getNormal(coordinate)
    };
}
TriangleNode        Triangle::createNode(Vector &position) {
    TriangleCoordinate bary = barycentric(position);
    return createNode(bary);
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
        if((this->nodes[i].position - intersection.base).mag_squared() <= EPSILON){
            if(!help){
                help = true;
            }else{
                return;
            }
        }
    }
    // determine if a node is cut or not. if so we can split into two triangles, if not we need 3.
    for(int i = 0; i < 3; i++){
        if((this->nodes[i].position - intersection.base).mag_squared() <= EPSILON){
            Vector p1 = intersection.base;
            Vector p2 = intersection.base + intersection.direction;

            Vector v1 = this->nodes[(i+1)%3].position;
            Vector v2 = this->nodes[(i+2)%3].position;

            Triangle t1 = {createNode(p1),createNode(p2),createNode(v1)};
            Triangle t2 = {createNode(p2),createNode(p1),createNode(v2)};

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
    Ray r1 {nodes[0].position, nodes[1].position-nodes[0].position};  // connection p0-p1
    Ray r2 {nodes[1].position, nodes[2].position-nodes[1].position};  // connection p1-p2
    Ray r3 {nodes[2].position, nodes[0].position-nodes[2].position};  // connection p0-p2
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
        cutoff  = this->getB().position;
        v1      = this->getA().position;
        v2      = this->getC().position;
    }
    // A is cutoff
    else if(c1 > 0 && c1 < 1 && c3 > 0 && c3 < 1){
        cutoff  = this->getA().position;
        v1      = this->getB().position;
        v2      = this->getC().position;
    }
    // C is cutoff
    else if(c2 > 0 && c2 < 1 && c3 > 0 && c3 < 1){
        cutoff  = this->getC().position;
        v1      = this->getA().position;
        v2      = this->getB().position;
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

    Triangle triC{createNode(cut1), createNode(cut2), createNode(cutoff)};
    Triangle tri1{createNode(cut1), createNode(cut2), createNode(v1)};
    Triangle tri2{createNode(  v1), createNode(cut2), createNode(v2)};

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




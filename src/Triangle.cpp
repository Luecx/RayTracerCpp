//
// Created by QuantumRange on 04-Feb-21.
//

#include "Triangle.h"

Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c) {

}

Triangle::Triangle(const Vector *points) {

}

Triangle::Triangle(Triangle &other) {

}

Triangle::Triangle(const Triangle &a, const Triangle &b) {

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

Vector Triangle::center() {
    Vector center{3};

    // TODO

    center[0] = getA()[0];
    center[1] = 0.0;
    center[2] = 0.0;

    return center;
}

const Triangle *Triangle::splitTriangle() {
    // TODO
    return nullptr;
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

Vector &Triangle::operator[](int index) {
    return points[index];
}

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
    os << "x: " << triangle.points[0] << ", y: " << triangle.points[1] << ", z: " << triangle.points[2];
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
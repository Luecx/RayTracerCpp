//
// Created by Luecx on 03.02.2021.
//

#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "cmath"


Vector::Vector() {
}


Vector::Vector(double x, double y, double z) {
    this->values[0] = x;
    this->values[1] = y;
    this->values[2] = z;
}

Vector::Vector(const Vector &vec) {
    std::memcpy(this->values, vec.values,3 * sizeof(double));
}

Vector::Vector(Vector &&vec) noexcept {
    std::memcpy(this->values, vec.values,3 * sizeof(double));
}

Vector::~Vector() {

}

Vector &Vector::operator=(const Vector &vec) {
    std::memcpy(this->values, vec.values, 3 * sizeof(double));
    return *this;
}

double &Vector::get(int index) {
    return values[index];
}

double Vector::get(int index) const {
    return values[index];
}

Vector Vector::cross(const Vector& other){
    return {get(1) * other(2) - get(2) * other(1),
            get(2) * other(0) - get(0) * other(2),
            get(0) * other(1) - get(1) * other(0)};
}


Vector &Vector::add(const Vector &other) {
    for(int i = 0; i < 3; i++){
        this->values[i] += other.get(i);
    }
    return *this;
}

Vector &Vector::sub(const Vector &other) {
    for(int i = 0; i < 3; i++){
        this->values[i] -= other.get(i);
    }
    return *this;
}

double Vector::dot(const Vector &other) {

    double res = 0;
    for(int i = 0; i < 3; i++){
        res += this->values[i] * other.values[i];
    }
    return res;
}


double Vector::mag_squared() {
    return dot(*this);
}

double Vector::mag() {
    return sqrt(mag_squared());
}

Vector &Vector::negate() {
    for(int i = 0; i < 3; i++){
        this->values[i] = -this->values[i];
    }
    return *this;
}

Vector &Vector::scale(double scalar) {
    for(int i = 0; i < 3; i++){
        this->values[i] *= scalar;
    }
    return *this;
}

Vector Vector::operator+(const Vector &vec) const{
    Vector v{*this};
    v.add(vec);
    return v;
}

Vector &Vector::operator+=(const Vector &vec) {
    return this->add(vec);
}

Vector Vector::operator-() {
    Vector v{*this};
    v.negate();
    return v;
}


Vector Vector::operator-(const Vector &vec) const{
    Vector v{*this};
    v.sub(vec);
    return v;
}

Vector &Vector::operator-=(const Vector &vec) {
    return this->sub(vec);
}

Vector &Vector::operator*=(const double scalar) {
    return this->scale(scalar);
}

Vector Vector::operator*(double scalar){
    Vector v{*this};
    v.scale(scalar);
    return v;
}

double Vector::operator*(const Vector &other) {
    return dot(other);
}

double &Vector::operator()(int index) {
    return this->get(index);
}

double Vector::operator()(int index) const {

    return this->get(index);
};

double &Vector::operator[](int index) {

    return this->get(index);
};

double Vector::operator[](int index) const {

    return this->get(index);
};

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    os << "[";

    for (int i = 0; i < 3; i++) {
        os << std::setprecision(10) << std::setw(18) << vector.values[i];
    }

    return os << "]";
}

bool Vector::operator==(const Vector &rhs) const {
    return values[0] == rhs.values[0] && values[1] == rhs.values[1] && values[2] == rhs.values[2];
}

bool Vector::operator!=(const Vector &rhs) const {
    return !(rhs == *this);
}


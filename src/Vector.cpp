//
// Created by Luecx on 03.02.2021.
//

#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "cmath"


Vector::Vector() {
    this->size = 3;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memset(this->values, 0, sizeof(double) * this->internalSize);
}

Vector::Vector(int size) {
    this->size = size;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memset(this->values, 0, sizeof(double) * this->internalSize);
}

Vector::Vector(double x, double y, double z) {
    this->size = 3;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    this->values[0] = x;
    this->values[1] = y;
    this->values[2] = z;
}

Vector::Vector(const Vector &vec) {
    this->size = vec.size;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memcpy(this->values, vec.values,this->internalSize * sizeof(double));
}

Vector::Vector(Vector &&vec) noexcept {
    this->size = vec.size;
    this->values = vec.values;
    vec.values = nullptr;
}

Vector::~Vector() {
    if (this->values != nullptr) {
        _mm_free(this->values);
        this->values = nullptr;
    }
}

Vector &Vector::operator=(const Vector &vec) {
    if (this->size != vec.size) {
        this->size = vec.size;
        this->internalSize = vec.internalSize;
        _mm_free(this->values);
        this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    }
    std::memcpy(this->values, vec.values, this->size * sizeof(double));
    return *this;
}

int Vector::entryCount(){
    return size;
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
//    __m256d *v1 = (__m256d *) this->values;
//    __m256d *v2 = (__m256d *) other.values;
//    for (int i = 0; i < internalSize / 4; i++) {
//        v1[i] = _mm256_add_pd(v1[i], v2[i]);
//    }
//    return *this;

    for(int i = 0; i < size; i++){
        this->values[i] += other.get(i);
    }
    return *this;
}

Vector &Vector::sub(const Vector &other) {
//    __m256d *v1 = (__m256d *) this->values;
//    __m256d *v2 = (__m256d *) other.values;
//    for (int i = 0; i < internalSize / 4; i++) {
//        v1[i] = _mm256_sub_pd(v1[i], v2[i]);
//    }
//    *v1 = _mm256_sub_pd(*v1, *v2);
//    return *this;
    for(int i = 0; i < size; i++){
        this->values[i] -= other.get(i);
    }
    return *this;
}

double Vector::dot(const Vector &other) {

    double res = 0;
    for(int i = 0; i < size; i++){
        res += this->values[i] * other.values[i];
    }
    return res;

//    double res = 0;
//    __m256d *v1 = (__m256d *) this->values;
//    __m256d *v2 = (__m256d *) other.values;
//    for (int i = 0; i < internalSize / 4; i++) {
//        __m256d xy = _mm256_mul_pd(v1[i], v2[i]);
//
//        __m128d xylow = _mm256_castpd256_pd128(xy);
//        __m128d xyhigh = _mm256_extractf128_pd(xy, 1);
//        __m128d sum1 = _mm_add_pd(xylow, xyhigh);
//
//        __m128d swapped = _mm_shuffle_pd(sum1, sum1, 0b01);
//        __m128d dotproduct = _mm_add_pd(sum1, swapped);
//        res += dotproduct[0];
//    }
//    return res;

}


double Vector::mag_squared() {
    return dot(*this);
}

double Vector::mag() {
    return sqrt(mag_squared());
}

Vector &Vector::negate() {
    for(int i = 0; i < size; i++){
        this->values[i] = -this->values[i];
    }
//    __m256d *v1 = (__m256d *) this->values;
//    for (int i = 0; i < internalSize / 4; i++) {
//        v1[i] = _mm256_sub_pd(_mm256_set1_pd(0.0), v1[i]);
//    }
    return *this;
}

Vector &Vector::scale(double scalar) {
//    __m256d *v1 = (__m256d *) this->values;
//    __m256d constant = _mm256_set1_pd(scalar);
//    for (int i = 0; i < internalSize / 4; i++) {
//        v1[i] = _mm256_mul_pd(constant, v1[i]);
//    }
//    return *this;
//
//    _mm256_store_pd(values, _mm256_mul_pd( _mm256_set1_pd(scalar),_mm256_load_pd(values)));
////    for (int i = 0; i < internalSize / 4; i++) {
////        v1[i] = _mm256_mul_pd(constant, v1[i]);
////    }
////    return *this;
    for(int i = 0; i < size; i++){
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

    for (int i = 0; i < vector.size; i++) {
        os << std::setprecision(10) << std::setw(18) << vector.values[i];
    }

    return os << "]";
}


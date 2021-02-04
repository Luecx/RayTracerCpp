//
// Created by Luecx on 03.02.2021.
//

#include <iostream>
#include <iomanip>
#include "vector.h"
#include "cmath"


vector::vector() {
    this->size = 3;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memset(this->values, 0, sizeof(double) * this->internalSize);
}


vector::vector(int size) {
    this->size = size;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memset(this->values, 0, sizeof(double) * this->internalSize);
}

vector::vector(const vector &vec) {
    this->size = vec.size;
    this->internalSize = FILL_TO_4(this->size);
    this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    std::memcpy(this->values, vec.values,this->internalSize * sizeof(double));
}

vector::vector(vector &&vec) noexcept {
    this->size = vec.size;
    this->values = vec.values;
    vec.values = nullptr;
}

vector::~vector() {
    if (this->values != nullptr) {
        _mm_free(this->values);
        this->values = nullptr;
    }
}

vector &vector::operator=(const vector &vec) {
    if (this->size != vec.size) {
        this->size = vec.size;
        this->internalSize = vec.internalSize;
        _mm_free(this->values);
        this->values = static_cast<double *> (_mm_malloc(this->internalSize * sizeof(double), 32));
    }
    std::memcpy(this->values, vec.values, this->size * sizeof(double));
    return *this;
}

vector &vector::operator=(vector &&vec) noexcept {

    delete[] this->values;
    this->size = vec.size;
    this->values = vec.values;
    vec.values = nullptr;

    return *this;
}

int vector::entryCount(){
    return size;
}

double &vector::get(int index) {
    return values[index];
}

double vector::get(int index) const {
    return values[index];
}

vector &vector::add(const vector &other) {
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

vector &vector::sub(const vector &other) {
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

double vector::dot(const vector &other) {

    double res = 0;
    for(int i = 0; i < size; i++){
        return this->values[i] * this->values[i];
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


double vector::mag_squared() {
    return dot(*this);
}

double vector::mag() {
    return sqrt(mag_squared());
}

vector &vector::negate() {
    for(int i = 0; i < size; i++){
        this->values[i] = -this->values[i];
    }
//    __m256d *v1 = (__m256d *) this->values;
//    for (int i = 0; i < internalSize / 4; i++) {
//        v1[i] = _mm256_sub_pd(_mm256_set1_pd(0.0), v1[i]);
//    }
    return *this;
}

vector &vector::scale(double scalar) {
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

vector &vector::operator+(const vector &vec) {
    vector *v = new vector{*this};
    v->add(vec);
    return *v;
}

vector &vector::operator+=(const vector &vec) {
    return this->add(vec);
}

vector &vector::operator-() {
    this->negate();
    return *this;
}


vector &vector::operator-(const vector &vec) {
    vector *v = new vector{*this};
    v->sub(vec);
    return *v;
}

vector &vector::operator-=(const vector &vec) {
    return this->sub(vec);
}

vector &vector::operator*=(const double scalar) {
    return this->scale(scalar);
}

double vector::operator*(const vector &other) {
    return dot(other);
}

double &vector::operator()(int index) {
    return this->get(index);
}

double vector::operator()(int index) const {

    return this->get(index);
};

double &vector::operator[](int index) {

    return this->get(index);
};

double vector::operator[](int index) const {

    return this->get(index);
};

std::ostream &operator<<(std::ostream &os, const vector &vector) {
    os << "[";

    for (int i = 0; i < vector.size; i++) {
        os << std::setprecision(5) << std::setw(15) << vector.values[i];
    }

    return os << "]";
}


//
// Created by Luecx on 03.02.2021.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <cstring>
#include <immintrin.h>
#include <ostream>

class Vector {
private:
    double values[3]{};
public:

    Vector();
    Vector(double x, double y, double z);
    Vector(const Vector& vec);
    Vector(Vector&& vec) noexcept ;
    virtual ~Vector();
    Vector& operator=(const Vector& vec);

    double& get(int index);
    double  get(int index) const;

    Vector  cross(const Vector& other);
    Vector& add(const Vector& other);
    Vector& sub(const Vector& other);
    double  dot(const Vector& other);
    double  mag_squared();
    double  mag();
    Vector& negate();
    Vector& scale(double scalar);

    Vector operator+(const Vector& vec) const;
    Vector& operator+=(const Vector& vec);

    Vector  operator-();
    Vector  operator-(const Vector& vec) const;
    Vector& operator-=(const Vector& vec);

    Vector& operator*=(double scalar);
    Vector  operator* (double scalar);
    double  operator* (const Vector& other);

    double& operator()(int index);
    double  operator()(int index) const;
    double& operator[](int index);
    double  operator[](int index) const;

    bool operator==(const Vector &rhs) const;
    bool operator!=(const Vector &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

};


#endif //RAYTRACER_VECTOR_H

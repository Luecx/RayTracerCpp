//
// Created by Luecx on 03.02.2021.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <cstring>
#include <immintrin.h>
#include <ostream>

#define FILL_TO_4(x) ((x) + ((x) % 4 != 0 ? 4 - (x) % 4 : 0))

class Vector {
private:
    int internalSize;
    double* values = nullptr;
    int size;
public:


    Vector();
    Vector(int size);
    Vector(double x, double y, double z);
    Vector(const Vector& vec);
    Vector(Vector&& vec) noexcept ;
    virtual ~Vector();
    Vector& operator=(const Vector& vec);

    int     entryCount();

    double& get(int index);
    double  get(int index) const;

    Vector& add(const Vector& other);
    Vector& sub(const Vector& other);
    double  dot(const Vector& other);
    double  mag_squared();
    double  mag();
    Vector& negate();
    Vector& scale(double scalar);

    Vector operator+(const Vector& vec);
    Vector& operator+=(const Vector& vec);

    Vector  operator-();
    Vector  operator-(const Vector& vec);
    Vector& operator-=(const Vector& vec);

    Vector& operator*=(double scalar);
    Vector  operator* (double scalar);
    double  operator* (const Vector& other);

    double& operator()(int index);
    double  operator()(int index) const;
    double& operator[](int index);
    double  operator[](int index) const;


    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

};


#endif //RAYTRACER_VECTOR_H

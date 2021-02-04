//
// Created by Luecx on 03.02.2021.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <cstring>
#include <immintrin.h>
#include <ostream>

#define FILL_TO_4(x) ((x) + ((x) % 4 != 0 ? 4 - (x) % 4 : 0))

class vector {
private:
    int internalSize;
    double* values = nullptr;
    int size;
public:


    explicit vector();
    explicit vector(int size);
    vector(const vector& vec);
    vector(vector&& vec) noexcept ;
    virtual ~vector();
    vector& operator=(const vector& vec);
    vector& operator=(vector&& vec) noexcept ;

    int     entryCount();

    double& get(int index);
    double  get(int index) const;

    vector& add(const vector& other);
    vector& sub(const vector& other);
    double  dot(const vector& other);
    double  mag_squared();
    double  mag();
    vector& negate();
    vector& scale(double scalar);

    vector& operator+(const vector& vec);
    vector& operator+=(const vector& vec);

    vector& operator-();
    vector& operator-(const vector& vec);
    vector& operator-=(const vector& vec);

    vector& operator*=(double scalar);
    double  operator* (const vector& other);

    double& operator()(int index);
    double  operator()(int index) const;
    double& operator[](int index);
    double  operator[](int index) const;


    friend std::ostream &operator<<(std::ostream &os, const vector &vector);

};


#endif //RAYTRACER_VECTOR_H

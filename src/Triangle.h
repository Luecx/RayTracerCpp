//
// Created by QuantumRange on 04-Feb-21.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include <ostream>
#include "Vector.h"

class Triangle {
private:
    Vector points[3];

public:

    Triangle();

    /**
     * Creates a triangle with points a, b, c
     * @param a The position for a
     * @param b The position for b
     * @param c The position for c
     */
    Triangle(const Vector &&a, const Vector &&b, const Vector &&c);

    /**
     * Creates a triangle with points a, b, c
     * @param a The position for a
     * @param b The position for b
     * @param c The position for c
     */
    Triangle(const Vector &a, const Vector &b, const Vector &c);
    /**
     * Creates a triangle from a list of points that is always 3 in size and starts with a and ends with c.
     * @param points The points to be inserted into the triangle.
     */
    Triangle(const Vector *points);
    /**
     * Copies another Triangle
     * @param other The Triangle which is to be copied.
     */
    Triangle(const Triangle &other);

    /**
     * Copies another Triangle
     * @param other The Triangle which is to be copied.
     */
    Triangle(Triangle &&other);


    Triangle &operator=(const Triangle &other);

    ~Triangle();

    /**
     * @return a
     */
    const Vector& getA();
    /**
     * @return b
     */
    const Vector& getB();
    /**
     * @return c
     */
    const Vector& getC();
    /**
     * @return The center of the triangle.
     */
    Vector center();

    /**
     * @return Two triangles that together form the old triangle.
     */
    const Triangle* splitTriangle();

    /**
     * Scales the triangle by scale.
     * @param scale is the scaled factor
     * @return the current triangle with all values multiply by scale.
     */
    Triangle& operator*=(double scale);
    /**
     * Scales the triangle by scale.
     * @param scale is the scaled factor
     * @return the current triangle with all values multiply by scale.
     */
    Triangle& operator* (double scale);

    /**
     * @param index is zero at a, one at b, and so on.
     * @return a at 0, b at 1, and c at 2.
     */
    Vector&   operator[](int index);

     /**
     * @param index is zero at a, one at b, and so on.
     * @return a at 0, b at 1, and c at 2.
     */
    Vector    operator[](int index) const;

    const Vector *getPoints() const;

    bool operator==(const Triangle &rhs) const;

    bool operator!=(const Triangle &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);

};


#endif //RAYTRACER_TRIANGLE_H

//
// Created by QuantumRange on 04-Feb-21.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include <ostream>
#include <vector>
#include "Vector.h"
#include "types.h"

struct TriangleCoordinate{
    // note that w is used for node A, u for B and v for C
    double u,v,w;

    void set(double u, double v) {
        this->u = u;
        this->v = v;
        this->w = 1 - u - v;
    }

    friend std::ostream &operator<<(std::ostream &os, const TriangleCoordinate &coordinate) {
        os << "u: " << coordinate.u << " v: " << coordinate.v << " w: " << coordinate.w;
        return os;
    }
};

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
    Vector center() const;

    /**
     * splits a triangle at a given plane.
     * it requires two vectors of triangles.
     * one is supposed to contain the triangles which are on the negative side of the split plane and
     * the other one will contain those which are on the positive side.
     * furthermore it requires the side which the triangle is on. this is relevant if the center is directly on the cut.
     * It is either +1 if its on the positive side or -1 if its on the negative side
     * @param p
     * @param lhs
     * @param rhs
     */
    void splitTriangle(Plane &p,  std::vector<Triangle> &lhs, std::vector<Triangle> &rhs, double originalSide);

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
    inline Vector&   operator[](int index){
        return points[index];
    }

     /**
     * @param index is zero at a, one at b, and so on.
     * @return a at 0, b at 1, and c at 2.
     */
     inline Vector    operator[](int index) const{
         return points[index];
    }

    const Vector *getPoints() const;


    bool operator==(const Triangle &rhs) const;

    bool operator!=(const Triangle &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);

};


#endif //RAYTRACER_TRIANGLE_H

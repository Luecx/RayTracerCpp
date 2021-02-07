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


struct TriangleNode {
    Vector position;
    Vector normal;

    bool operator==(const TriangleNode &rhs) const {
        return position == rhs.position &&
               normal == rhs.normal;
    }

    bool operator!=(const TriangleNode &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const TriangleNode &node) {
        os << "position: " << node.position << " normal: " << node.normal;
        return os;
    }

};

class Triangle {
private:

    TriangleNode nodes[3];

public:

    Triangle();

    /**
     * Creates a triangle with points a, b, c
     * @param a The position for a
     * @param b The position for b
     * @param c The position for c
     */
    Triangle(const TriangleNode &&a, const TriangleNode &&b, const TriangleNode &&c);

    /**
     * Creates a triangle with points a, b, c
     * @param a The position for a
     * @param b The position for b
     * @param c The position for c
     */
    Triangle(const TriangleNode &a, const TriangleNode &b, const TriangleNode &c);

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

    /**
     * copies another triangle
     * @param other
     * @return
     */
    Triangle &operator=(const Triangle &other);

    ~Triangle();

    /**
     * @return a
     */
    const TriangleNode& getA();
    /**
     * @return b
     */
    const TriangleNode& getB();
    /**
     * @return c
     */
    const TriangleNode& getC();

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
    inline TriangleNode&   operator[](int index){
        return nodes[index];
    }

     /**
     * @param index is zero at a, one at b, and so on.
     * @return a at 0, b at 1, and c at 2.
     */
     inline TriangleNode    operator[](int index) const{
         return nodes[index];
    }

    /**
     * equality comparison. compares the nodes
     * @param rhs
     * @return
     */
    bool operator==(const Triangle &rhs) const;

    /**
     * inequality comparison. compares the nodes
     * @param rhs
     * @return
     */
    bool operator!=(const Triangle &rhs) const;

    /**
     * stream output operator
     * @param os
     * @param triangle
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);

    /**
     * computes barycentric coordinates for a given position
     * @param vec
     * @return
     */
    TriangleCoordinate  barycentric(Vector& vec);

    /*
     * barycentric interpolation for normal
     */
    Vector              getNormal  (TriangleCoordinate &coordinate);

    /*
     * barycentric interpolation for position
     */
    Vector              getPosition(TriangleCoordinate &coordinate);

    /**
     * creates a new node containing normal/position etc for a given triangle coordinate
     * @return
     */
    TriangleNode        createNode(TriangleCoordinate &coordinate);

    /**
     * creates a new node containing normal/position etc for a given triangle coordinate
     * @return
     */
    TriangleNode        createNode(Vector &position);
};


#endif //RAYTRACER_TRIANGLE_H

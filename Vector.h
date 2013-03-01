///
/// @file Vector.h
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	A vector quantity.
///

#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

#include <cmath>
#include <iostream>
using namespace std;

namespace Radiosity {

class Vector {

    ///
    /// @name operator<<
    ///
    /// @description
    /// 	Vector output operator.
    ///
    /// @param os - the output stream
    /// @param other - the vector to output
    /// @return - the output stream
    ///
    friend ostream& operator<<(ostream& os, const Vector& other);

    friend inline Vector add(const Vector& a, const Vector& b)
    {
        return Vector(a._x + b._x, a._y + b._y, a._z + b._z);
    }

    friend inline Vector crossProduct(const Vector &v1, const Vector &v2)
    {
        return Vector(v1._y * v2._z - v1._z * v2._y,
                      v1._z * v2._x - v1._x * v2._z,
                      v1._x * v2._y - v1._y * v2._x);
    }

    friend inline float dotProduct(const Vector &v1, const Vector &v2)
    {
        return (v1._x * v2._x + v1._y * v2._y + v1._z * v2._z);
    }

    friend inline Vector negateVector(const Vector &v)
    {
        return Vector(-v._x, -v._y, -v._z);
    }

    friend inline Vector scalarMultiply(const Vector &v, float scalar)
    {
        return Vector(v._x * scalar, v._y * scalar, v._z * scalar);
    }

public:

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of this vector
    /// @param y - y-axis component of this vector
    /// @param z - z-axis component of this vector
    /// @return - void
    ///
    Vector(float x, float y, float z);

    Vector(const Point &p1, const Point &p2);

    ///
    /// @name Vector
    ///
    /// @description
    /// 	Default constructor
    ///
    /// @return - void
    ///
    Vector();

    ///
    /// @name ~Vector
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Vector();

    inline Point Translate(const Point &p);

    ///
    /// @name Normalize
    ///
    /// @description
    /// 	Normalizes the vector to a unit length.
    ///
    /// @return - void
    ///
    inline void Normalize();

    ///
    /// @name operator*=
    ///
    /// @description
    /// 	Times-equals operator.
    ///
    /// @param s - a scalar floating point value
    /// @return - address of this argument
    ///
    inline Vector& operator*=(float s);

private:

    ///
    /// @name _x
    ///
    /// @description
    ///		The x-axis component of this vector.
    ///
    float _x;

    ///
    /// @name _y
    ///
    /// @description
    ///		The y-axis component of this vector.
    ///
    float _y;

    ///
    /// @name _z
    ///
    /// @description
    ///		The z-axis component of this vector.
    ///
    float _z;


};  // class Vector

// Normalize
inline void Vector::Normalize() {
    double s = 1.0 / (double) sqrt(_x * _x + _y * _y + _z * _z);
    _x *= s; _y *= s; _z *= s;
}

inline Point Vector::Translate(const Point &p)
{
	return Point(p.x + _x, p.y + _y, p.z + _z);
}

// operator*=
inline Vector& Vector::operator*=(float s) {
    _x *= s;
    _y *= s;
    _z *= s;
    return *this;
}

}   // namespace Radiosity

#endif






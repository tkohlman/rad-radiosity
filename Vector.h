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
    
    friend inline Vector operator+(const Vector& a, const Vector& b) {
        return Vector(a._x + b._x, a._y + b._y, a._z + b._z);
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
    /// @name operator*
    /// 
    /// @description
    /// 	Scalar multiplication operator.
    ///
    /// @param scalar - scalar multiplier
    /// @return - Vector multiplied by scalar value
    ///
    inline Vector operator*(const float& scalar) const;
    
    ///
    /// @name operator*
    /// 
    /// @description
    /// 	Dot product operator.
    ///
    /// @param other - the second vector
    /// @return - Vector dot product
    ///
    inline float operator*(const Vector& other) const;

    ///
    /// @name operator^
    /// 
    /// @description
    /// 	Cross product operator.
    ///
    /// @param other - the second vector
    /// @return - Vector cross product
    ///
    inline Vector operator^(const Vector& other) const;
    
    ///
    /// @name operator=
    /// 
    /// @description
    /// 	Equals operator.
    ///
    /// @param other - the second vector
    /// @return - address of this argument
    ///
    inline Vector& operator=(const Vector& other);
    
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
    
    ///
    /// @name operator-
    /// 
    /// @description
    /// 	Negation operator.
    ///
    /// @return - negation of this vector
    ///
    inline Vector operator-() const;

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

// operator*
inline Vector Vector::operator*(const float& scalar) const {
    return Vector(_x * scalar, _y * scalar, _z * scalar);
}

// operator*
inline float Vector::operator*(const Vector& other) const {
    return (_x * other._x + _y * other._y + _z * other._z);
}

// operator^
inline Vector Vector::operator^(const Vector& other) const {
    return Vector(_y * other._z - _z * other._y,
                  _z * other._x - _x * other._z,
                  _x * other._y - _y * other._x);
}

// operator=
inline Vector& Vector::operator=(const Vector& other) {
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

// operator*=
inline Vector& Vector::operator*=(float s) {
    _x *= s;
    _y *= s;
    _z *= s;
    return *this;
}

// operator-
inline Vector Vector::operator-() const {
    return Vector(-_x, -_y, -_z);
}

}   // namespace Radiosity

#endif






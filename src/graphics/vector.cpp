///
/// @file Vector.cpp
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	A vector quantity.
///

#include "vector.h"

namespace Radiosity
{

Vector::Vector(float x, float y, float z) :
    _x(x),
    _y(y),
    _z(z)
{
}

Vector::Vector(const Point &p1, const Point &p2):
    _x(p1.x - p2.x),
    _y(p1.y - p2.y),
    _z(p1.z - p2.z)
{
}

Vector::Vector():
    _x(0),
    _y(0),
    _z(0)
{
}

}   // namespace Radiosity

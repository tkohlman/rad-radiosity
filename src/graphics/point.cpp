///
/// @file Point.cpp
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	A 3D point representation.
///

#include "point.h"
#include <GL/glut.h>

namespace Radiosity
{

Point::Point(float x, float y, float z, Color c):
    x(x),
    y(y),
    z(z),
    mColor(c),
    mCount(1)
{
}

Point::Point(float x, float y, float z):
    x(x),
    y(y),
    z(z),
    mCount(1)
{
}

Point::Point(const Point& other):
    x(other.x),
    y(other.y),
    z(other.z),
    mColor(other.mColor),
    mCount(other.mCount)
{
}

Point::Point():
    x(0),
    y(0),
    z(0),
    mCount(1)
{
}

Point::~Point()
{
}

void Point::Draw()
{
    glColor3f(mColor.R(), mColor.G(), mColor.B());
    glVertex3f(x, y, z);
}

void Point::DrawNoColor()
{
    glVertex3f(x, y, z);
}

void Point::UpdateColor(const Color& color)
{
    float reciprocal = 1.0 / mCount;

    if (!(color == Color()))
    {
        Color weighted_color = (mColor * mCount) + color;

        mColor = weighted_color * reciprocal;
        ++mCount;
    }
}

}   // namespace Radiosity

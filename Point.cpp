///
/// @file Point.cpp
/// 
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	A 3D point representation.
///

#include "Point.h"
#include <GL/glut.h>

namespace Radiosity {

//
// Constructor
//
Point::Point(float x, float y, float z, Color c) :
    x(x), y(y), z(z), mColor(c), mCount(1) {
}

//
// Constructor
//
Point::Point(float x, float y, float z) :
    x(x), y(y), z(z), mCount(1) {
}

//
// Copy Constructor
//
Point::Point(const Point& other) :
    x(other.x), y(other.y), z(other.z), mColor(other.mColor),
    mCount(other.mCount) {
}

//
// Default Constructor
//
Point::Point() :
    x(0), y(0), z(0), mCount(1) {
}

//
// Destructor
//
Point::~Point() {
}

void Point::Draw()
{
    glColor3f(mColor.R(), mColor.G(), mColor.B());
    glVertex3f(x, y, z);

	return;
}

void Point::DrawNoColor()
{
    glVertex3f(x, y, z);

	return;
}

//
// To String
//
ostream& operator<<(ostream& os, const Point& other) {
    os << "(" << other.x << ", " << other.y << ", " << other.z << ")";
    return os;
}

//
// UpdateColor
//
void Point::UpdateColor(const Color& color, float weight) {

    float reciprocal = 1.0 / mCount;

    if (!(color == Color())) {
        Color weighted_color = (mColor * mCount) + color;
        
        mColor = weighted_color * reciprocal;
        //cout << "reciprocal " << reciprocal << endl;
        ++mCount;
    }
}

}   // namespace Radiosity




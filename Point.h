///
/// @file Point.h
/// 
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	A 3D point representation.
///

#ifndef POINT_H
#define POINT_H

//#include "Vector.h"
#include "Color.h"

#include <cmath>
#include <iostream>
using namespace std;

namespace Radiosity {

class Point {

    ///
    /// @name operator<<
    /// 
    /// @description
    /// 	Point output operator.
    ///
    /// @param os - the output stream
    /// @param other - the point to output
    /// @return - the output stream
    ///
    friend ostream& operator<<(ostream& os, const Point& other);

    friend class Vector;

public:

    ///
    /// @name Point
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of constructed point
    /// @param y - y-axis component of constructed point
    /// @param z - z-axis component of constructed point
    /// @param c - the color of the point
    /// @return - void
    ///
    Point(float x, float y, float z, Color c);
    
    ///
    /// @name Point
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param x - x-axis component of constructed point
    /// @param y - y-axis component of constructed point
    /// @param z - z-axis component of constructed point
    /// @return - void
    ///
    Point(float x, float y, float z);

    ///
    /// @name Point
    /// 
    /// @description
    /// 	Copy Constructor
    ///
    /// @param other - Point object to copy
    /// @return - void
    ///
    Point(const Point& other);
    
    ///
    /// @name Point
    /// 
    /// @description
    /// 	Default Constructor
    ///
    /// @return - void
    ///
    Point();

    ///
    /// @name ~Point
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Point();
    
    ///
    /// @name GetColor
    ///
    /// @description
    ///     Accessor for the _color member variable.
    ///
    /// @return - the color of this point
    ///
    inline Color GetColor() const;
    
    ///
    /// @name operator=
    /// 
    /// @description
    /// 	Equals assignment operator.
    ///
    /// @param other - the second point
    /// @return - address of this argument
    ///
    inline Point& operator=(const Point& other);
    
    ///
    /// @name distance
    ///
    /// @description
    ///     Calculates distance between two points.
    ///
    /// @param other - second point in distance calculation
    /// @return - the distance between this point and the other point
    ///
    inline float DistanceTo(const Point& other) const;
    
    ///
    /// @name UpdateColor
    /// 
    /// @description
    /// 	Average in the given color using the given weight
    ///
    /// @param color - the color to average in.
    /// @param weight - the weight to use for this color
    ///
    void UpdateColor(const Color& color, float weight);
    
    void Draw();
    void DrawNoColor();

private:

    float x;
    float y;
    float z;

    ///
    /// @name _color
    ///
    /// @description
    ///     The color of this point.
    ///
    Color mColor;
    
    ///
    /// @name mCount
    /// 
    /// @description
    /// 	Number of colors which have been averaged in
    ///
    int mCount;


};  // class Point

//
// GetColor
//
inline Color Point::GetColor() const {
    return (mColor);
}

// operator=
inline Point& Point::operator=(const Point& other) {
    x = other.x;
    y = other.y;
    z = other.z;
        
    return *this;
}

//
// distance
//
inline float Point::DistanceTo(const Point& other) const {
    
    return sqrt( pow(x - other.x, 2) +
                 pow(y - other.y, 2) +
                 pow(z - other.z, 2) );
}

}   // namespace Radiosity

#endif



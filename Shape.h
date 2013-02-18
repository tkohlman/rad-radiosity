///
/// @file Shape.h
/// 
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	Abstract shape class.
///

#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include "Color.h"
#include "Vector.h"

#include <cstdlib>
using namespace std;

namespace Radiosity {

class Shape {

public:

    ///
    /// @name Shape
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param c - the color of the shape
    /// @return - void
    ///
    Shape(Color c);

    ///
    /// @name ~Shape
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    virtual ~Shape();

    ///
    /// @name GetColor
    /// 
    /// @description
    /// 	Accessor for _color member variable.
    ///
    /// @return - the color of the shape.
    ///
    Color GetColor();

    ///
    /// @name Intersect
    /// 
    /// @description
    /// 	Determines if a ray intersects the shape.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - intersection point closest to ray origin, NULL if no
    ///           intersection occurs
    ///
    virtual Point* Intersect(Vector v, Point o) = 0;

private:

    ///
    /// @name _color
    ///
    /// @description
    ///		The color of the shape.
    ///
    Color _color;

};  // class Shape

}   // namespace Radiosity

#endif

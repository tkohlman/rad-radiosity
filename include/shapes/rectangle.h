///
/// @file Rectangle.h
/// 
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	Rectangle shape representation.
///

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "color.h"
#include "point.h"
#include "vector.h"
#include "patch.h"


#include <vector>
using namespace std;

namespace Radiosity {

class Rectangle : public Shape {

public:
    
    ///
    /// @name Rectangle
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param a - first point in ABCD
    /// @param b - second point in ABCD
    /// @param c - third point in ABCD
    /// @param d - fourth point in ABCD
    /// @param color - color of the rectangle
    /// @param emission - emissive quantity of the rectangle
    /// @return - void
    ///
    Rectangle(Point a, Point b, Point c, Point d, Color color, float emit);

    ///
    /// @name ~Rectangle
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Rectangle();
    
    ///
    /// @name Intersect
    /// 
    /// @description
    /// 	Determines if a ray intersects the rectangle.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - intersection point closest to ray origin, nullptr if no
    ///           intersection occurs
    ///
    Point* Intersect(Vector v, Point o);
    
    void Subdivide(float patchSize);

    ///
    /// @name A
    /// 
    /// @description
    /// 	Accessor for _a member variable.
    ///
    /// @return - A point of ABCD rectangle
    ///    
    Point A() const;

    ///
    /// @name B
    /// 
    /// @description
    /// 	Accessor for _b member variable.
    ///
    /// @return - B point of ABCD rectangle
    ///    
    Point B() const;

    ///
    /// @name C
    /// 
    /// @description
    /// 	Accessor for _c member variable.
    ///
    /// @return - C point of ABCD rectangle
    ///    
    Point C() const;
    
    ///
    /// @name D
    /// 
    /// @description
    /// 	Accessor for _d member variable.
    ///
    /// @return - D point of ABCD rectangle
    ///    
    Point D() const;

    float emission;

private:

    ///
    /// @name _a
    ///
    /// @description
    ///		The first point of the rectangle.
    ///
    Point _a;
    
    
    ///
    /// @name _b
    ///
    /// @description
    ///		The second point of the rectangle.
    ///
    Point _b;
    
    ///
    /// @name _c
    ///
    /// @description
    ///		The third point of the rectangle.
    ///
    Point _c;
    
    ///
    /// @name _d
    ///
    /// @description
    ///		The fourth point of the rectangle.
    ///
    Point _d;
    
    
    ///
    /// @name _normal
    ///
    /// @description
    ///		The vector normal to the plane formed by the rectangle.
    ///
    Vector _normal;

    vector<Patch*> *mPatches;


};  // class Rectangle

}   // namespace Radiosity

#endif




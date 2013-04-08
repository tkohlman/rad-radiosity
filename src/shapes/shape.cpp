///
/// @file Shape.cpp
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	Abstract shape class implementation.
///

#include "shape.h"

namespace Radiosity
{

Shape::Shape(Color c):
    _color(c)
{
}

Shape::~Shape()
{
}

Color Shape::GetColor()
{
    return (_color);
}

}   // namespace Radiosity




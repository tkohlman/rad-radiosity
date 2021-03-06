///
/// @file Color.cpp
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	An RGB color representation.
///

#include "color.h"

namespace Radiosity
{

Color::Color(float r, float g, float b):
    _r(r),
    _g(g),
    _b(b)
{
}

Color::Color(const Color& other):
    _r(other._r),
    _g(other._g),
    _b(other._b)
{
}

Color::Color():
    _r(0),
    _g(0),
    _b(0)
{
}

Color::~Color()
{
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    os << "("
       << color.R()
       << "r, "
       << color.G()
       << "g, "
       << color.B()
       << "b)";
    return os;
}

}   // namespace Radiosity

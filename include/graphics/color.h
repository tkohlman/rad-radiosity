///
/// @file Color.h
///
/// @author	Thomas Kohlman
/// @date 30 December
///
/// @description
/// 	An RGB color representation.
///

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace Radiosity
{

class Color
{
public:

    ///
    /// @name Color
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param r - the red component of the constructed color
    /// @param g - the green component of the constructed color
    /// @param b - the blue component of the constructed color
    /// @return <returns>
    ///
    Color(float r, float g, float b);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Copy constructor
    ///
    /// @param other - Color object to copy
    /// @return - void
    ///
    Color(const Color& other);

    ///
    /// @name Color
    ///
    /// @description
    /// 	Default constructor
    ///
    /// @return - void
    ///
    Color();

    ///
    /// @name ~Color
    ///
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~Color();

    ///
    /// @name R
    ///
    /// @description
    /// 	Accessor for the _r member variable.
    ///
    /// @return - the red component of this color
    ///
    inline float R() const;

    ///
    /// @name G
    ///
    /// @description
    /// 	Accessor for the _g member variable.
    ///
    /// @return - the green component of this color
    ///
    inline float G() const;

    ///
    /// @name B
    ///
    /// @description
    /// 	Accessor for the _b member variable.
    ///
    /// @return - the blue component of this color
    ///
    inline float B() const;

    inline Color& operator=(const Color& other);
    inline bool operator==(const Color& other) const;
    inline Color operator*(float scalar) const;
    inline Color operator*(const Color& other) const;
    inline Color operator+(const Color& other) const;
    inline Color& operator+=(const Color& other);

private:

    ///
    /// @name _r
    ///
    /// @description
    ///		The red component of this color.
    ///
    float _r;

    ///
    /// @name _g
    ///
    /// @description
    ///		The green component of this color.
    ///
    float _g;

    ///
    /// @name _b
    ///
    /// @description
    ///		The blue component of this color.
    ///
    float _b;

};  // class Color

inline Color Color::operator*(const Color& other) const
{
    return Color(_r * other._r, _g * other._g, _b * other._b);
}

inline Color Color::operator*(float scalar) const
{
    return Color(_r * scalar, _g * scalar, _b * scalar);
}

inline Color& Color::operator+=(const Color& other)
{
    _r += other._r;
    _g += other._g;
    _b += other._b;
    return *this;
}

inline Color Color::operator+(const Color& other) const
{
    return Color(_r + other._r, _g + other._g, _b + other._b);
}

inline float Color::R() const
{
    return (_r);
}

inline float Color::G() const
{
    return (_g);
}

inline float Color::B() const
{
    return (_b);
}

inline Color& Color::operator=(const Color& other)
{
    _r = other.R();
    _g = other.G();
    _b = other.B();
    return *this;
}

inline bool Color::operator==(const Color& other) const
{
    return ((_r == other.R()) && (_g == other.G()) && (_b == other.B()));
}

}   // namespace Radiosity

#endif

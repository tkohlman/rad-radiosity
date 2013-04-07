///
/// @file Patch.h
///
/// @author	Thomas Kohlman
/// @date 31 December 2011
///
/// @description
/// 	Declares a radiosity patch data structure.
///

#ifndef PATCH_H
#define PATCH_H

#include "point.h"
#include "vector.h"

#include <vector>
#include <map>

namespace Radiosity {

class Patch;
typedef std::map< Patch*, std::vector< std::pair< Patch*, float > > > FormFactorMap;

class Patch {

public:

    ///
    /// @name Patch
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param a - point A in patch ABCD
    /// @param b - point B in patch ABCD
    /// @param c - point C in patch ABCD
    /// @param d - point D in patch ABCD
    /// @param color - base color of the patch
    /// @param Emission - total emission of this patch
    /// @return - void
    ///
    Patch(Point *a, Point *b, Point *c, Point *d, Color col, float emission);

    ///
    /// @name ~Patch
    ///
    /// @description
    /// 	Destructor
    ///
    ~Patch();

    ///
    /// @name Intersect
    ///
    /// @description
    /// 	Determines if the ray defined by the vector, v, and the origin, o,
    ///     intersects the patch. If it does, it returns the distance along
    ///     the ray that the center of the patch is from the origin.
    ///
    /// @param v - direction vector of the ray
    /// @param o - origin of the ray
    /// @return - distance to intersection point.
    ///
    float Intersect(Vector v, Point o);

    ///
    /// @name AddViewablePatch
    ///
    /// @description
    /// 	Record a patch with line of sight to this patch.
    ///
    /// @param patch - the patch with LOS
    ///
    void AddViewablePatch(Patch *patch);

    ///
    /// @name RemoveViewablePatch
    ///
    /// @description
    /// 	Remove a patch from the line of sight vector.
    ///
    /// @param patch - the patch to remove
    ///
    void RemoveViewablePatch(Patch *patch);

    ///
    /// @name UpdateFormFactor
    ///
    /// @description
    /// 	Update the form factor between this patch and one of the patches
    ///     with line of sight. The value is added to the current form factor
    ///     value for the given patch.
    ///
    /// @param index - the index of the second patch into the los vector
    ///
    void UpdateFormFactor(int index, float formFactor);

    ///
    /// @name UpdateIncidence
    ///
    /// @description
    /// 	Update the incidence value of this patch.
    ///
    void UpdateIncidence();

    ///
    /// @name UpdateExidence
    ///
    /// @description
    /// 	Update the exidence value of this patch.
    ///
    void UpdateExidence();

    /// @name UpdateCornerColors
    ///
    /// @description
    /// 	Update the vertex colors for this patch
    ///
    void UpdateCornerColors();

    void Draw();
    void DrawOutline();
    void DrawNormal();

    // Accessors
    const Vector& GetNormal() const;
    const Point& GetCenter() const;

    const Point* GetA() const;

    std::vector<Patch*> *GetViewablePatches() const;
    std::vector<float> *GetFormFactors() const;

    bool Contains(Point p) const;

    bool IsFacing(const Patch *other) const;

private:

    Point *mA;
    Point *mB;
    Point *mC;
    Point *mD;

    Color mColor;

    Vector mPatchNormal;

    Point mCenterPoint;

    static int mNumPatches;


    static Radiosity::FormFactorMap formFactorMap;

    float mArea;


    float mReflectance;
    Color mEmission;
    Color mIncidence;
    Color mExidence;

    std::vector<Patch*> *mViewablePatches;
    std::vector<float> *mFormFactors;

};  // class Patch



//
// GetNormal
//
inline const Vector& Patch::GetNormal() const {
    return mPatchNormal;
}

//
// GetCenter
//
inline const Point& Patch::GetCenter() const {
    return mCenterPoint;
}

//
// GetA
//
inline const Point* Patch::GetA() const {
    return mA;
}

//
// GetViewablePatches
//
inline std::vector<Patch*> *Patch::GetViewablePatches() const {
    return mViewablePatches;
}

//
// GetFormFactors
//
inline std::vector<float> *Patch::GetFormFactors() const {
    return mFormFactors;
}

}   // namespace Radiosity

#endif



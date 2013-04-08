///
/// @file Hemicube.h
///
/// @author	Thomas Kohlman
/// @date 5 January 2012
///
/// @description
/// 	A hemicube representation to aid with form factor calculation.
///

#ifndef HEMICUBE_H
#define HEMICUBE_H

#include "point.h"
#include "vector.h"
#include "patch.h"
#include "rectangle.h"

#include <vector>
#include <cstdlib>
#include <iostream>

#define WIDTH 1.0

namespace Radiosity
{

class Hemicube
{

public:

    ///
    /// @name Hemicube
    ///
    /// @description
    /// 	Constructor
    ///
    /// @param subdivisions - resolution of the hemicube
    ///
    Hemicube(int subdivisions, std::vector<Rectangle*> *quads);

    ///
    /// @name ~Hemicube
    ///
    /// @description
    /// 	Destructor
    ///
    ~Hemicube();

    ///
    /// @name TraceHemicube
    ///
    /// @description
    /// 	Position the hemicube over the given patch and trace energy through
    ///     all faces.
    ///
    /// @param patch - the patch indicating where to position the hemicube
    ///
    void TraceHemicube(Patch *patch);

    ///
    /// @name GetLeftMultiplier
    ///
    /// @description
    /// 	Accessor for the left face multiplier.
    ///
    /// @return - the left face multiplier
    ///
    const std::vector< std::vector<float>* > *GetLeftMultiplier() const;

    ///
    /// @name GetTopMultiplier
    ///
    /// @description
    /// 	Accessor for the top face multiplier.
    ///
    /// @return - the top face multiplier
    ///
    const std::vector< std::vector<float>* > *GetTopMultiplier() const;

    ///
    /// @name GetRightMultiplier
    ///
    /// @description
    /// 	Accessor for the right face multiplier.
    ///
    /// @return - the right face multiplier
    ///
    const std::vector< std::vector<float>* > *GetRightMultiplier() const;

    ///
    /// @name GetBottomMultiplier
    ///
    /// @description
    /// 	Accessor for the bottom face multiplier.
    ///
    /// @return - the bottom face multiplier
    ///
    const std::vector< std::vector<float>* > *GetBottomMultiplier() const;

    ///
    /// @name GetFrontMultiplier
    ///
    /// @description
    /// 	Accessor for the front face multiplier.
    ///
    /// @return - the front face multipler
    ///
    const std::vector< std::vector<float>* > *GetFrontMultiplier() const;

private:

    ///
    /// @name BuildMultipliers
    ///
    /// @description
    /// 	Calculate the energy values for all faces of the hemicube.
    ///
    void BuildMultipliers( void );

    ///
    /// @name NormalizeMultipliers
    ///
    /// @description
    /// 	Normalizes all multipliers so that the total energy of all faces
    ///     of the hemicube adds to unity.
    ///
    ///
    void NormalizeMultipliers( void );

    ///
    /// @name BuildMultiplier
    ///
    /// @description
    /// 	This is a private helper function for the private function,
    ///     BuildMultipliers. It builds the multiplier for a single face
    ///     of the hemicube.
    ///
    /// @param centerPoint - center point of the hemicube
    /// @param starting point - starting corner of the face for which to build
    ///                         the multiplier
    /// @param patchNormal - the normal of the patch located at the center of
    ///                      the hemicube
    /// @param faceNormal - the normal of the face for which the multiplier
    ///                     is being built
    /// @param row - vector specifying the row direction
    /// @param col - vector specifying the column direction
    /// @param numRows - the number of rows on this face
    /// @param numCols - the number of columns on this face
    ///
    /// @return - the multiplier for this face
    ///
    std::vector< std::vector<float>* > *BuildMultiplier(Point centerPoint,
        Point startingPoint, Vector patchNormal, Vector faceNormal, Vector row,
        Vector col, int numRows, int numCols);

    ///
    /// @name TraceFace
    ///
    /// @description
    /// 	Trace a single face of the hemicube. This is a private helper
    ///     function for the public TraceHemicube function.
    ///
    /// @param patch - the patch at the origin of the hemicube
    /// @param startingPoint - the origin of the hemicube
    /// @param row - a vector that specifies the row
    /// @param col - a vector that specifies the column
    /// @param multiplier - the precomputed multiplier to use for this face
    ///
    void TraceFace(Patch *patch, Point startingPoint, Vector row, Vector col,
                   std::vector< std::vector<float>* > *multiplier);

    ///
    /// @name mSubdivisions
    ///
    /// @description
    ///		Resolution of the hemicube.
    ///
    int mSubdivisions;

    ///
    /// @name mLeftMultiplier
    ///
    /// @description
    ///		Energy values for the left face of the hemicube.
    ///
    std::vector< std::vector<float>* > *mLeftMultiplier;

    ///
    /// @name mTopMultiplier
    ///
    /// @description
    ///		Energy values for the top face of the hemicube.
    ///
    std::vector< std::vector<float>* > *mTopMultiplier;

    ///
    /// @name mRightMultiplier
    ///
    /// @description
    ///		Energy values for the right face of the hemicube.
    ///
    std::vector< std::vector<float>* > *mRightMultiplier;

    ///
    /// @name mBottomMultiplier
    ///
    /// @description
    ///		Energy values for the bottom face of the hemicube.
    ///
    std::vector< std::vector<float>* > *mBottomMultiplier;

    ///
    /// @name mFrontMultipliers
    ///
    /// @description
    ///		Energy values for the front face of the hemicube.
    ///
    std::vector< std::vector<float>* > *mFrontMultiplier;

    std::vector<Rectangle*> *mShapes;

};  // class Hemicube

}   // namesapce radiosity

#endif

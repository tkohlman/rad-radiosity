///
/// @file PatchCalculator.h
/// 
/// @author	Thomas Kohlman
/// @date 2 February 2012
///
/// @description
/// 	Divides a scene into patches.
///

#ifndef PATCH_CALCULATOR_H
#define PATCH_CALCULATOR_H

#include "point.h"
#include "vector.h"
#include "patch.h"
#include "rectangle.h"

#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

namespace Radiosity {

class PatchCalculator {

public:

    ///
    /// @name PatchCalculator
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @param patchSize - the size to make patches
    ///
    PatchCalculator(float patchSize);
    
    ///
    /// @name ~PatchCalculator
    /// 
    /// @description
    /// 	Destructor
    ///
    ~PatchCalculator();
    
    ///
    /// @name Subdivide
    /// 
    /// @description
    /// 	Performs the patch subdivision algorithm.
    ///
    /// @param quads - vector of quadrilaterals to divide
    /// @param patchs - the patches resulting from the subdivision
    ///
    void Subdivide(vector<Rectangle*> *quads, vector<Patch*> *patches);
    
private:

    ///
    /// @name mPatchSize
    /// 
    /// @description
    /// 	Maximum size of the patch. It may be smaller.
    ///
    float mPatchSize;
    
};  // class PatchCalculator

}   // namesapce Radiosity

#endif


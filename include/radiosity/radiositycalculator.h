///
/// @file RadiosityCalculator.h
///
/// @author	Thomas Kohlman
/// @date 2 February 2012
///
/// @description
/// 	Implements a progressive radiosity algorithm.
///

#ifndef RADIOSITY_CALCULATOR_H
#define RADIOSITY_CALCULATOR_H

#include "point.h"
#include "vector.h"
#include "patch.h"

#include <vector>
#include <cstdlib>
#include <iostream>

namespace Radiosity {

class RadiosityCalculator {

public:

    ///
    /// @name CalculateRadiosity
    ///
    /// @description
    /// 	Implements a progressive radiosity solution.
    ///
    /// @param patches - vector containing patches in the scene
    /// @param numIterations - number of iterations to run through the
    ///                        progressive solution
    ///
    void CalculateRadiosity(std::vector<Patch*> *patches, int numIterations);

};  // class RadiosityCalculator

}   // namespace Radiosity

#endif






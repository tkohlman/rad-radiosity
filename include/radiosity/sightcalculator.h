///
/// @file SightCalculator.h
///
/// @author	Thomas Kohlman
/// @date 6 January 2012
///
/// @description
/// 	Contains functions to calculate visibility between patches.
///

#ifndef SIGHT_CALCULATOR_H
#define SIGHT_CALCULATOR_H

#include "patch.h"

namespace Radiosity {

class SightCalculator {

public:

    ///
    /// @name SightCalculator
    ///
    /// @description
    /// 	Constructor
    ///
    SightCalculator();

    ///
    /// @name ~SightCalculator
    ///
    /// @description
    /// 	Destructor
    ///
    ~SightCalculator();

    ///
    /// @name CalculateLOS
    ///
    /// @description
    /// 	Calculates los between all pairs of patches
    ///
    /// @param patches - vector of patches
    ///
    void CalculateLOS(std::vector<Patch*> *patches);

private:

    ///
    /// @name RunQuickElimination
    ///
    /// @description
    /// 	Runs quick normal-based LOS elimination
    ///
    /// @param patches - vector of patches
    ///
    void RunQuickElimination(std::vector<Patch*> *patches);

    ///
    /// @name RunInterceptTest
    ///
    /// @description
    /// 	Calculates los between all pairs of patches using intercept tests
    ///
    /// @param patches - vector of patches
    ///
    void RunInterceptTest(std::vector<Patch*> *patches);


};  // class SightCalculator

}   // namespace Radiosity

#endif






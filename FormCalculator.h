///
/// @file FormCalculator.h
/// 
/// @author	Thomas Kohlman
/// @date 5 January 2012
///
/// @description
/// 	Collection of routines responsible for calculating form factors 
///     between patches.
///

#ifndef FORM_CALCULATOR_H
#define FORM_CALCULATOR_H

#include "Hemicube.h"
#include "Patch.h"
#include "Rectangle.h"

namespace Radiosity {

class FormCalculator {

public:

    ///
    /// @name FormCalculator
    ///
    /// @description
    ///     Constructor
    ///
    FormCalculator(vector<Rectangle*> *quads);
    
    ///
    /// @name ~FormCalculator
    ///
    /// @description
    ///     Destructor
    ///
    ~FormCalculator();

    ///
    /// @name CalculateFormFactors
    ///
    /// @description
    ///     Using the hemicube method, this function calculates the form
    ///     factors between all pairs of patches.
    ///
    void CalculateFormFactors(vector<Patch*> *patches);

private:

    ///
    /// @name mHemicube
    ///
    /// @description
    ///     The precomputed hemicube used to calculate form factors for
    ///     each patch.
    ///
    Hemicube mHemicube;
    
};  // class FormCalculator

}   // namespace Radiosity

#endif



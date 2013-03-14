///
/// @file FormCalculator.cpp
/// 
/// @author	Thomas Kohlman
/// @date 5 January 2012
///
/// @description
/// 	Collection of routines responsible for calculating form factors 
///     between patches.
///

#include "formcalculator.h"

namespace Radiosity {

// Constructor
FormCalculator::FormCalculator(vector<Rectangle*> *quads) :
    mHemicube(25, quads) {
}

// Destructor
FormCalculator::~FormCalculator() {

}

// CalculateFormFactors
void FormCalculator::CalculateFormFactors(vector<Patch*> *patches) {

    vector<Patch*>::const_iterator iter = patches->begin();
    
    for (; iter != patches->end(); ++iter) {
        mHemicube.TraceHemicube(*iter);
    }
}


}   // namespace Radiosity





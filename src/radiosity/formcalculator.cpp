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

namespace Radiosity
{

FormCalculator::FormCalculator(std::vector<Rectangle*> *quads):
    mHemicube(25, quads)
{
}

FormCalculator::~FormCalculator()
{
}

void FormCalculator::CalculateFormFactors(std::vector<Patch*> *patches)
{
    std::vector<Patch*>::const_iterator iter = patches->begin();

    for (; iter != patches->end(); ++iter)
    {
        mHemicube.TraceHemicube(*iter);
    }
}

}   // namespace Radiosity

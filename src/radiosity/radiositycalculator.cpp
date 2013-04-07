///
/// @file RadiosityCalculator.cpp
///
/// @author	Thomas Kohlman
/// @date 2 February 2012
///
/// @description
/// 	Implements a progressive radiosity algorithm.
///

#include "radiositycalculator.h"

namespace Radiosity
{

//
// CalculateRadiosity
//
void RadiosityCalculator::CalculateRadiosity(std::vector<Patch*> *patches,
    int numIterations) {

    // The progressive radiosity algorithm pseudocode is as follows:
    //
    //      for each iteration:
    //          select a patch, p
    //          for every other patch, q
    //              calculate the form factor between p and q
    //              based on the form factor:
    //                  update the reflectance of patch q
    //                  update the emission of patch q
    //              set emission of patch p to zero
    //

    for (int iteration = 0; iteration < numIterations; ++iteration) {



        // Each patch collects light from the scene. Add up this light from
        // all visible patches to get the total incident light for this
        // iteration.

        std::vector<Patch*>::iterator piter = patches->begin();

        for (; piter != patches->end(); ++piter) {

            // Update the patch's incidence
            (*piter)->UpdateIncidence();
        }

        // Update the exident light for each patch, now that all the incident
        // light is accounted for.
        piter = patches->begin();

        for (; piter != patches->end(); ++piter) {

            // Update the patche's exidence
            (*piter)->UpdateExidence();
        }
    }
}

}	// namespace Radiosity

///
/// @file SightCalculator.cpp
///
/// @author	Thomas Kohlman
/// @date 6 January 2012
///
/// @description
/// 	Contains functions to calculate visibility between patches.
///

#include "sightcalculator.h"

namespace Radiosity {

//
// Constructor
//
SightCalculator::SightCalculator() {

}

//
// Destructor
//
SightCalculator::~SightCalculator() {

}

//
// CalculateLOS
//
void SightCalculator::CalculateLOS(std::vector<Patch*> *patches) {
    // Run quick elimination
    RunQuickElimination(patches);

    // Test the remaining patches with intercepts
    //RunInterceptTest(patches);
}

//
// RunQuickElimination
//
void SightCalculator::RunQuickElimination(std::vector<Patch*> *patches) {

    std::vector<Patch*>::iterator iter1 = patches->begin();

    // For each patch
    for (; iter1 != patches->end(); ++iter1) {

        // Look at every FOLLOWING patch (no need to compare twice) since
        // line of sight is reciprocal
        std::vector<Patch*>::iterator iter2 = iter1 + 1;

        for (; iter2 != patches->end(); ++iter2) {

            Patch *patch1 = *iter1;
            Patch *patch2 = *iter2;

            if (patch1->IsFacing(patch2))
            {
				 // Assuming nothing is in the way, these patches can see each
				// other, so add each one to the other's line of sight vector.
				patch1->AddViewablePatch(patch2);
				patch2->AddViewablePatch(patch1);
            }

        } // loop over all following patches

    } // loop over all patches

} // RunQuickElimination


//
// RunInterceptTest
//
void SightCalculator::RunInterceptTest(std::vector<Patch*> *patches) {

    // Loop over all patches
    std::vector<Patch*>::const_iterator iter1 = patches->begin();
    for (; iter1 != patches->end(); ++iter1) {

        // Each patch has a line of sight vector that contains patches it would
        // be able to see if only those two patches existed. This function
        // eliminates patches from the line of sight vector if they are blocked
        // by other patches in the line of sight vector.

        Patch *patch1 = *iter1;

        // Loop over line of sight vector
        std::vector<Patch*>::iterator iter2 = patch1->GetViewablePatches()->begin();
        for (; iter2 != patch1->GetViewablePatches()->end(); ++iter2) {

            Patch *patch2 = *iter2;

            // Calculate the vector between the patches
            Vector ray(patch2->GetCenter(), patch1->GetCenter());
            normalize(ray);

            float shortest_distance =
                patch1->GetCenter().DistanceTo(patch2->GetCenter());

            // Look at all other patches in the line of sight vector to see if
            // another patch is closer along this ray
            std::vector<Patch*>::const_iterator iter3 = patch1->GetViewablePatches()->begin();
            for (; iter3 != patch1->GetViewablePatches()->end(); ++iter3) {


                Patch *patch3 = *iter3;

                // Do not compare a patch against itself
                if (patch2 == patch3) {
                    continue;
                }

                // Calculate the distance between patch 1 and patch 3 along the
                // ray. If this distance is shorter than the distance to patch
                // 2 along this ray, patch 3 is closer than, and therefore
                // blocking, patch 2.
                float new_distance = patch3->Intersect(ray, patch1->GetCenter());

                if ((new_distance > 0) && (new_distance < shortest_distance)) {

                    // Remove patch2 from patch1's line of sight and patch1
                    // ftom patch2's line of sight
                    patch2->RemoveViewablePatch(patch1);
                    patch1->RemoveViewablePatch(patch2);
                    --iter2;

                    break;
                }

            } // for (siter; siter != patches->end(); ++siter)

        } // Loop over line of sight vector

    } // Loop over all patches

} // RunInterceptTest

} // namespace Radiosity





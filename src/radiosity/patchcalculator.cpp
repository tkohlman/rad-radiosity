///
/// @file PatchCalculator.cpp
///
/// @author	Thomas Kohlman
/// @date 2 February 2012
///
/// @description
/// 	Divides a scene into patches.
///

#include "patchcalculator.h"

namespace Radiosity
{

PatchCalculator::PatchCalculator(float patchSize) :
    mPatchSize(patchSize) {
}

PatchCalculator::~PatchCalculator() { }

//
// Subdivide
//
void PatchCalculator::Subdivide(vector<Rectangle*> *quads, vector<Patch*> *patches) {

    vector<Rectangle*>::iterator iter = quads->begin();
    // For each quad
    for (; iter != quads->end(); ++iter) {

        Rectangle *quad = *iter;

        // Calculate the number of patches along one axis
        float distance_i = quad->A().DistanceTo(quad->B());
        float dimension_i = distance_i / mPatchSize;
        int size_i = int(dimension_i);
        float remainder_i = dimension_i - size_i;

        if (remainder_i > 0) {
            ++size_i;
        }

        // Calculate the number of patches along the other axis
        float distance_j = quad->A().DistanceTo(quad->D());
        float dimension_j = distance_j / mPatchSize;
        int size_j = int(dimension_j);
        float remainder_j = dimension_j - size_j;

        if (remainder_j > 0) {
            ++size_j;
        }

        // Create a two-dimensional vector to hold points
        vector< vector<Point*> > points(size_i + 1, vector<Point*>(size_j + 1,
            (Point*)nullptr));



        Vector AB((*iter)->B(), (*iter)->A());
        Vector AD((*iter)->D(), (*iter)->A());
        float len_AB = (*iter)->B().DistanceTo((*iter)->A());
        float len_AD = (*iter)->D().DistanceTo((*iter)->A());

        normalize(AB);
        normalize(AD);

        Point *p1;

        // Create the starting point
        p1 = new Point((*iter)->A());

        // Loop in AD direction
        for (int j = 0; j <= size_j; ++j) {

            // add p1 to the list
            points.at(0).at(j) = p1;

            Point *p2 = p1;

            // Loop in AB direction
            for (int i = 0; i < size_i; ++i) {

                Point *p3;

                // Check boundary
                if (i == size_i - 1) {
                    p3 = new Point(scalarMultiply(AB, len_AB).Translate(*p1));
                } else {
                    p3 = new Point(scalarMultiply(AB, mPatchSize).Translate(*p2));
                }

                // add p3 to the list
                points.at(i+1).at(j) = p3;

                // Update p2
                p2 = p3;
            }

            // Update p1
            if (j == size_j - 1) {
                p1 = new Point(scalarMultiply(AD, len_AD).Translate((*iter)->A()));
            } else {
                p1 = new Point(scalarMultiply(AD, mPatchSize).Translate(*p1));
            }
        }

        // Create the patches
        // Loop in AD direction
        for (int j = 0; j < size_j; ++j) {

            // Loop in AB direction
            for (int i = 0; i < size_i; ++i) {

                Point *A = points.at(i).at(j);
                Point *B = points.at(i+1).at(j);
                Point *C = points.at(i+1).at(j+1);
                Point *D = points.at(i).at(j+1);

                // Create the patch
                Patch *p = new Patch(A, B, C, D, quad->GetColor(), quad->emission);
                patches->push_back(p);
            }
        }
    }

}   // Subdivide

}	// namespace Radiosity

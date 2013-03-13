///
/// @file Hemicube.cpp
///
/// @author	Thomas Kohlman
/// @date 5 January 2012
///
/// @description
/// 	A hemicube representation to aid with form factor calculation.
///
/// Version:
/// 	$Id: Hemicube.cpp,v 1.1 2012/01/06 01:25:23 thomas Exp thomas $
///

#include "Hemicube.h"
using namespace Radiosity;

namespace Radiosity {

// Constructor
Hemicube::Hemicube(int subdivisions, vector<Rectangle*> *quads) :
    mSubdivisions(subdivisions), mShapes(quads) {
    BuildMultipliers();
    NormalizeMultipliers();
}

// Destructor
Hemicube::~Hemicube() {

    // Clean up dynamic memory
    vector< vector<float>* >::iterator iter;

    // Left Multiplier
    for (iter = mLeftMultiplier->begin();
         iter != mLeftMultiplier->end(); ++iter) {
        delete *iter;
    }
    delete mLeftMultiplier;

    // Top Multiplier
    for (iter = mTopMultiplier->begin();
         iter != mTopMultiplier->end(); ++iter) {
        delete *iter;
    }
    delete mTopMultiplier;

    // Right Multiplier
    for (iter = mRightMultiplier->begin();
         iter != mRightMultiplier->end(); ++iter) {
        delete *iter;
    }
    delete mRightMultiplier;

    // Bottom Multiplier
    for (iter = mBottomMultiplier->begin();
         iter != mBottomMultiplier->end(); ++iter) {
        delete *iter;
    }
    delete mBottomMultiplier;

    // Front Multiplier
    for (iter = mFrontMultiplier->begin();
         iter != mFrontMultiplier->end(); ++iter) {
        delete *iter;
    }
    delete mFrontMultiplier;
}

void Hemicube::TraceHemicube(Patch *patch) {

    // For the multipliers, we can just put the hemicube at the origin
    Point origin = patch->GetCenter();

    // The normal is the look-at for the camera. We'll use the -z-axis.
    Vector normal = patch->GetNormal();

    // Define one of the corners
    Point corner = *patch->GetA();

    // Vector vN goes from the center point to corner N
    Vector v1(corner, origin);
    Vector v2 = crossProduct(normal, v1);

    normalize(v1);
    normalize(v2);

    Vector v3 = negateVector(v1);
    Vector v4 = negateVector(v2);

    // The distance from the center to the corners on the same plane is equal
    // to the square root of one-half the width of the hemicube.
    float distance = sqrt(WIDTH/2);

    // Create the 8 points that define the cube.
    Point p1 = scalarMultiply(v1, distance).Translate(origin);
	Point p2 = scalarMultiply(v2, distance).Translate(origin);
	Point p3 = scalarMultiply(v1, -distance).Translate(origin);
	Point p4 = scalarMultiply(v2, -distance).Translate(origin);
	Point p5 = scalarMultiply(normal, (WIDTH/2)).Translate(p1);
	Point p6 = scalarMultiply(normal, (WIDTH/2)).Translate(p2);
	Point p7 = scalarMultiply(normal, (WIDTH/2)).Translate(p3);
	Point p8 = scalarMultiply(normal, (WIDTH/2)).Translate(p4);

    // The vector that is normal to the left face is the sum of the vectors
    // that extend from the center point to the two corners of the left face.
    Vector left_normal = add(v1, v4);
    normalize(left_normal);

    // The vector that is normal to the top face is the sum of the vectors
    // that extend from the center point to the two corners of the top face.
    Vector top_normal = add(v1, v2);
    normalize(top_normal);

    // The vector that is normal to the right face is the sum of the vectors
    // that extend from the center point to the two corners of the right face.
    Vector right_normal = add(v2, v3);
    normalize(right_normal);

    // The vector that is normal to the bottom face is the sum of the vectors
    // that extend from the center point to the two corners of the bottom face.
    Vector bottom_normal = add(v3, v4);
    normalize(bottom_normal);

    // The vector that is normal to the front face is equal to the normal
    // vector of the patch. In this case, the patch is the x-y plane.
    Vector front_normal = normal;

    // Trace left face
    TraceFace(patch, p1, left_normal, bottom_normal, front_normal,
        mLeftMultiplier);

    // Trace top face
    TraceFace(patch, p1, top_normal, front_normal, right_normal,
        mTopMultiplier);

    // Trace right face
    TraceFace(patch, p6, right_normal, bottom_normal, negateVector(front_normal),
        mRightMultiplier);

    // Trace bottom face
    TraceFace(patch, p8, bottom_normal, negateVector(front_normal), right_normal,
        mBottomMultiplier);

    // Trace front face
    TraceFace(patch, p5, front_normal, bottom_normal, right_normal,
        mFrontMultiplier);
}

// GetLeftMultiplier
const vector< vector<float>* > *Hemicube::GetLeftMultiplier() const {
    return mLeftMultiplier;
}

// GetTopMultiplier
const vector< vector<float>* > *Hemicube::GetTopMultiplier() const {
    return mTopMultiplier;
}

// GetRightMultiplier
const vector< vector<float>* > *Hemicube::GetRightMultiplier() const {
    return mRightMultiplier;
}

// GetBottomMultiplier
const vector< vector<float>* > *Hemicube::GetBottomMultiplier() const {
    return mBottomMultiplier;
}

// GetFrontMultiplier
const vector< vector<float>* > *Hemicube::GetFrontMultiplier() const {
    return mFrontMultiplier;
}

// Build Multipliers
void Hemicube::BuildMultipliers() {

    // For the multipliers, we can just put the hemicube at the origin
    Point origin(0.0, 0.0, 0.0);

    // The normal is the look-at for the camera. We'll use the -z-axis.
    Vector normal(0.0, 0.0, -1.0);

    // Define one of the corners
    Point corner(-WIDTH/2, WIDTH/2, 0);

    // Vector vN goes from the center point to corner N
    Vector v1(corner, origin);
    Vector v2 = crossProduct(normal, v1);

    normalize(v1);
    normalize(v2);

    Vector v3 = negateVector(v1);
    Vector v4 = negateVector(v2);

    // The distance from the center to the corners on the same plane is equal
    // to the square root of one-half the width of the hemicube.
    float distance = sqrt(WIDTH/2);

    // Create the 8 points that define the cube.
    Point p1 = scalarMultiply(v1, distance).Translate(origin);
	Point p2 = scalarMultiply(v2, distance).Translate(origin);
	Point p3 = scalarMultiply(v1, -distance).Translate(origin);
	Point p4 = scalarMultiply(v2, -distance).Translate(origin);
	Point p5 = scalarMultiply(normal, (WIDTH/2)).Translate(p1);
	Point p6 = scalarMultiply(normal, (WIDTH/2)).Translate(p2);
	Point p7 = scalarMultiply(normal, (WIDTH/2)).Translate(p3);
	Point p8 = scalarMultiply(normal, (WIDTH/2)).Translate(p4);

    // The vector that is normal to the left face is the sum of the vectors
    // that extend from the center point to the two corners of the left face.
    Vector left_normal = add(v1, v4);
    normalize(left_normal);

    // The vector that is normal to the top face is the sum of the vectors
    // that extend from the center point to the two corners of the top face.
    Vector top_normal = add(v1, v2);
    normalize(top_normal);

    // The vector that is normal to the right face is the sum of the vectors
    // that extend from the center point to the two corners of the right face.
    Vector right_normal = add(v2, v3);
    normalize(right_normal);

    // The vector that is normal to the bottom face is the sum of the vectors
    // that extend from the center point to the two corners of the bottom face.
    Vector bottom_normal = add(v3, v4);
    normalize(bottom_normal);

    // The vector that is normal to the front face is equal to the normal
    // vector of the patch. In this case, the patch is the x-y plane.
    Vector front_normal = normal;

    // Build the left multiplier
    mLeftMultiplier = BuildMultiplier(origin, p1, normal, left_normal,
        bottom_normal, front_normal, mSubdivisions, mSubdivisions/2);

    // Build the top multiplier
    mTopMultiplier = BuildMultiplier(origin, p1, normal, top_normal,
        front_normal, right_normal, mSubdivisions/2, mSubdivisions);

    // Build the right multiplier
    mRightMultiplier = BuildMultiplier(origin, p6, normal, right_normal,
        bottom_normal, negateVector(front_normal), mSubdivisions, mSubdivisions/2);

    // Build the bottom multiplier
    mBottomMultiplier = BuildMultiplier(origin, p8, normal, bottom_normal,
        negateVector(front_normal), right_normal, mSubdivisions/2, mSubdivisions);

    // Build the front multiplier
    mFrontMultiplier = BuildMultiplier(origin, p5, normal, front_normal,
        bottom_normal, right_normal, mSubdivisions, mSubdivisions);

}

// Build Multiplier
vector< vector<float>* > *Hemicube::BuildMultiplier(Point centerPoint,
    Point startingPoint, Vector patchNormal, Vector faceNormal, Vector row,
    Vector col, int numRows, int numCols) {

    // Create the multiplier vector with the determined number of rows and
    // columns.
    vector< vector<float>* > *multiplier =
        new vector< vector<float>* >();
    for (int i(0); i < numRows; ++i) {
        multiplier->push_back(new vector<float>(numCols, 0));
    }

    // This algorithm fires rays through the surface pixels of the hemicube.
    // The pixel width is defined by 1/N.
    float dp = 1.0 / mSubdivisions;

    // Make sure the row and column vectors are normalized. Then weight them
    // by dp.
    normalize(row);
    normalize(col);
    row = scalarMultiply(row, dp);
    col = scalarMultiply(col, dp);

    // We will be looping in two directions.The outer loop determines the
    // row index of the multiplier table. The inner loop determines the column
    // index of the multiplier table.

    Point e = scalarMultiply(add(row, col), 0.5).Translate(startingPoint);

    for (int r(0); r < numRows; ++r) {

        Point f = e;

        for (int c(0); c < numCols; ++c) {

            // Create the ray, which depends on the face you are dealing with.
            Vector ray(f, centerPoint);
            normalize(ray);

            // Compensate for the hemicube's shape. This involves multiplying
            // the value by the dot product between the face normal and the
            // ray.
            float value = dotProduct(ray, faceNormal);

            // Apply Lambert's cosine law, which says that the apparent
            // brightness of a surface is proportional to the cosine of the
            // angle between the surface normal and the direction of light.
            value *= dotProduct(ray, patchNormal);

            // Set the value in the multiplier map
            multiplier->at(r)->at(c) = value;

            // Update f
            f = col.Translate(f);

        } // loop over column index

        // Update e
        e = row.Translate(e);

    } // loop over row index

    return multiplier;
}

void Hemicube::NormalizeMultipliers() {

    // Compute the sum of all the faces of all multipliers
    float sum = 0;

    // Left multiplier
    for (int i(0); i < mLeftMultiplier->size(); ++i) {
        for (int j(0); j < mLeftMultiplier->at(i)->size(); ++j) {
            sum += mLeftMultiplier->at(i)->at(j);
        }
    }

    // Top multiplier
    for (int i(0); i < mTopMultiplier->size(); ++i) {
        for (int j(0); j < mTopMultiplier->at(i)->size(); ++j) {
            sum += mTopMultiplier->at(i)->at(j);
        }
    }

    // Right multiplier
    for (int i(0); i < mRightMultiplier->size(); ++i) {
        for (int j(0); j < mRightMultiplier->at(i)->size(); ++j) {
            sum += mRightMultiplier->at(i)->at(j);
        }
    }

    // Bottom multiplier
    for (int i(0); i < mBottomMultiplier->size(); ++i) {
        for (int j(0); j < mBottomMultiplier->at(i)->size(); ++j) {
            sum += mBottomMultiplier->at(i)->at(j);
        }
    }

    // Front multiplier
    for (int i(0); i < mFrontMultiplier->size(); ++i) {
        for (int j(0); j < mFrontMultiplier->at(i)->size(); ++j) {
            sum += mFrontMultiplier->at(i)->at(j);
        }
    }

    // Now divide by the sum

    // Left multiplier
    for (int i(0); i < mLeftMultiplier->size(); ++i) {
        for (int j(0); j < mLeftMultiplier->at(i)->size(); ++j) {
            mLeftMultiplier->at(i)->at(j) /= sum;
        }
    }

    // Top multiplier
    for (int i(0); i < mTopMultiplier->size(); ++i) {
        for (int j(0); j < mTopMultiplier->at(i)->size(); ++j) {
            mTopMultiplier->at(i)->at(j) /= sum;
        }
    }

    // Right multiplier
    for (int i(0); i < mRightMultiplier->size(); ++i) {
        for (int j(0); j < mRightMultiplier->at(i)->size(); ++j) {
            mRightMultiplier->at(i)->at(j) /= sum;
        }
    }

    // Bottom multiplier
    for (int i(0); i < mBottomMultiplier->size(); ++i) {
        for (int j(0); j < mBottomMultiplier->at(i)->size(); ++j) {
            mBottomMultiplier->at(i)->at(j) /= sum;
        }
    }

    // Front multiplier
    for (int i(0); i < mFrontMultiplier->size(); ++i) {
        for (int j(0); j < mFrontMultiplier->at(i)->size(); ++j) {
            mFrontMultiplier->at(i)->at(j) /= sum;
        }
    }
}

void Hemicube::TraceFace(Patch *patch, Point startingPoint, Vector faceNormal,
    Vector row, Vector col, vector< vector<float>* > *multiplier) {

    // The origin of the ray is the center point of the patch.
    Point origin = patch->GetCenter();

    // This algorithm fires rays through the surface pixels of the hemicube.
    // The pixel width is defined by 1/N.
    float dp = 1.0 / mSubdivisions;

    // Make sure the row and column vectors are normalized. Then weight them
    // by dp.
    normalize(row);
    normalize(col);
    row = scalarMultiply(row, dp);
    col = scalarMultiply(col, dp);

    // We will be looping in two directions.The outer loop determines the
    // row index of the multiplier table. The inner loop determines the column
    // index of the multiplier table.

    Point e = scalarMultiply(add(row, col), 0.5).Translate(startingPoint);

    vector<Patch*>::const_iterator iter;

    for (int r(0); r < multiplier->size(); ++r) {

        Point f = e;

        for (int c(0); c < multiplier->at(r)->size(); ++c) {

            // Create the ray, which depends on the face you are dealing with.
            Vector ray(f, origin);
            normalize(ray);

            int index = 0;


            // Determine the shape that this ray intersects. Knowing the shape
            // eliminates the patches from all other objects (a significant
            // improvement).
            Point *closest = nullptr;

            // find the closest intersection
            int shape2 = 0;
            int shape = 0;
            for (; shape < mShapes->size(); ++shape) {

                // Get the intersection point
                Point *p = (mShapes->at(shape))->Intersect(ray, origin);

                if (p != nullptr) {

                    // There was an intersection

                    if (closest == nullptr) {

                        // p is closest, by default
                        closest = p;
                        shape2 = shape;

                    } else if (origin.DistanceTo(*p) < origin.DistanceTo(*closest)) {

                        // p is closer
                        closest = p;
                        shape2 = shape;
                    }
                }
            }

            //cout << endl << "looking for id: " << shape2 << endl;

            // Fire the ray at every patch with line of sight
            for (iter = patch->GetViewablePatches()->begin();
                 iter != patch->GetViewablePatches()->end(); ++iter) {

                //cout << "parent id: " << (*iter)->GetParentId() << endl;

                //if ((*iter)->GetParentId() == shape2) {

                    // If the ray intersects this patch
                    if ((*iter)->Intersect(ray, origin) > 0) {
                    //if (closest != nullptr && (*iter)->Contains(*closest)) {
                        // Update the form factor for this patch
                        patch->UpdateFormFactor(index, multiplier->at(r)->at(c));
                        break;
                    }
                //}

                ++index;
            }

            // Update f
            f = col.Translate(f);

        } // loop over column index

        // Update e
        e = row.Translate(e);

    } // loop over row index
}


}   // namespace Radiosity


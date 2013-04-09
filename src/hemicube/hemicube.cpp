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

#include "hemicube.h"
#include "multiplier.h"

namespace Radiosity
{

Hemicube::Hemicube(int subdivisions, std::vector<Rectangle*> *quads) :
    mSubdivisions(subdivisions),
    mShapes(quads)
{
    BuildMultipliers();
    NormalizeMultipliers();
}

Hemicube::~Hemicube()
{
    delete m_left_multiplier;
    delete m_top_multiplier;
    delete m_right_multiplier;
    delete m_bottom_multiplier;
    delete m_front_multiplier;
}

void Hemicube::TraceHemicube(Patch *patch)
{
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
    TraceFace(patch, p1, bottom_normal, front_normal, m_left_multiplier);

    // Trace top face
    TraceFace(patch, p1, front_normal, right_normal, m_top_multiplier);

    // Trace right face
    TraceFace(patch, p6, bottom_normal, negateVector(front_normal),
        m_right_multiplier);

    // Trace bottom face
    TraceFace(patch, p8, negateVector(front_normal), right_normal,
        m_bottom_multiplier);

    // Trace front face
    TraceFace(patch, p5, bottom_normal, right_normal, m_front_multiplier);
}

void Hemicube::BuildMultipliers()
{
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

    m_left_multiplier = new Multiplier(origin,
                                      p1,
                                      normal,
                                      left_normal,
                                      bottom_normal,
                                      front_normal,
                                      mSubdivisions,
                                      mSubdivisions/2);

    // Build the top multiplier
    m_top_multiplier = new Multiplier(origin,
                                     p1,
                                     normal,
                                     top_normal,
                                     front_normal,
                                     right_normal,
                                     mSubdivisions/2,
                                     mSubdivisions);

    // Build the right multiplier
    m_right_multiplier = new Multiplier(origin,
                                       p6,
                                       normal,
                                       right_normal,
                                       bottom_normal,
                                       negateVector(front_normal),
                                       mSubdivisions,
                                       mSubdivisions/2);

    // Build the bottom multiplier
    m_bottom_multiplier = new Multiplier(origin,
                                        p8,
                                        normal,
                                        bottom_normal,
                                        negateVector(front_normal),
                                        right_normal,
                                        mSubdivisions/2,
                                        mSubdivisions);

    // Build the front multiplier
    m_front_multiplier = new Multiplier(origin,
                                       p5,
                                       normal,
                                       front_normal,
                                       bottom_normal,
                                       right_normal,
                                       mSubdivisions,
                                       mSubdivisions);
}

void Hemicube::NormalizeMultipliers()
{
    float normalization_factor = m_left_multiplier->sum() +
                                 m_top_multiplier->sum() +
                                 m_right_multiplier->sum() +
                                 m_bottom_multiplier->sum() +
                                 m_front_multiplier->sum();

    m_left_multiplier->normalize(normalization_factor);
    m_top_multiplier->normalize(normalization_factor);
    m_right_multiplier->normalize(normalization_factor);
    m_bottom_multiplier->normalize(normalization_factor);
    m_front_multiplier->normalize(normalization_factor);
}

void Hemicube::TraceFace(Patch *patch,
                         Point startingPoint,
                         Vector row,
                         Vector col,
                         Multiplier *multiplier)
{
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

    std::vector<Patch*>::const_iterator iter;

    for (unsigned int r(0); r < multiplier->height(); ++r)
    {
        Point f = e;

        for (unsigned int c(0); c < multiplier->width(); ++c)
        {
            // Create the ray, which depends on the face you are dealing with.
            Vector ray(f, origin);
            normalize(ray);

            int index = 0;

            // Determine the shape that this ray intersects. Knowing the shape
            // eliminates the patches from all other objects (a significant
            // improvement).
            Point *closest = nullptr;

            // find the closest intersection
            //int shape2 = 0;
            for (unsigned int shape = 0; shape < mShapes->size(); ++shape)
            {

                // Get the intersection point
                Point *p = (mShapes->at(shape))->Intersect(ray, origin);

                if (p != nullptr)
                {
                    // There was an intersection
                    if (closest == nullptr)
                    {
                        // p is closest, by default
                        closest = p;
                        //shape2 = shape;
                    }
                    else if (origin.DistanceTo(*p) < origin.DistanceTo(*closest))
                    {
                        // p is closer
                        closest = p;
                        //shape2 = shape;
                    }
                }
            }

            //cout << endl << "looking for id: " << shape2 << endl;

            // Fire the ray at every patch with line of sight
            for (iter = patch->GetViewablePatches()->begin();
                 iter != patch->GetViewablePatches()->end(); ++iter)
            {

                //cout << "parent id: " << (*iter)->GetParentId() << endl;

                //if ((*iter)->GetParentId() == shape2) {

                    // If the ray intersects this patch
                    if ((*iter)->Intersect(ray, origin) > 0)
                    {
                    //if (closest != nullptr && (*iter)->Contains(*closest)) {
                        // Update the form factor for this patch
                        patch->UpdateFormFactor(index, multiplier->weight_at(r, c));
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

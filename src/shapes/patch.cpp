///
/// @file Patch.cpp
///
/// @author	Thomas Kohlman
/// @date 31 December 2011
///
/// @description
/// 	Implements a radiosity patch data structure.
///

#define COLOR_BLENDING

#include "patch.h"
#include <GL/glut.h>

namespace Radiosity
{

int Patch::mNumPatches(0);

//
// Constructor
//
Patch::Patch(Point *a, Point *b, Point *c, Point *d, Color col, float emission):
    mA(a),
    mB(b),
    mC(c),
    mD(d),
    mColor(col)
{
    // Calculate the normal vector
    Vector AB(*mB, *mA);
    Vector BC(*mC, *mB);
    mPatchNormal = crossProduct(BC, AB);
    normalize(mPatchNormal);

    // Calculate the area
    float dAB = mA->DistanceTo(*mB);
    float dBC = mB->DistanceTo(*mC);
    mArea = dAB * dBC;

    // Calculate the center point
    Vector AC(*mC, *mA);
    normalize(AC);
    float dist = sqrt((dAB/2) * (dAB/2) + (dBC/2) * (dBC/2));
    mCenterPoint = scalarMultiply(AC, dist).Translate(*mA);

    // Emission
    mEmission = col * emission;

    // Create the patch line of sight vector
    mViewablePatches = new std::vector<Patch*>;

    // Create the form factor vector
    mFormFactors = new std::vector<float>;

    mReflectance = .85;

    mIncidence = Color();

    mExidence = mEmission;
}

Patch::~Patch()
{
    delete mViewablePatches;
    delete mFormFactors;
}

void Patch::Draw()
{
    glBegin(GL_QUADS);
	mA->Draw();
	mB->Draw();
	mC->Draw();
	mD->Draw();
    glEnd();
}

void Patch::DrawOutline()
{
    glLineWidth(2);
    glColor3f(0,0,0);

    glBegin(GL_LINES);
	mA->DrawNoColor();
	mB->DrawNoColor();
	mB->DrawNoColor();
	mC->DrawNoColor();
	mC->DrawNoColor();
	mD->DrawNoColor();
	mD->DrawNoColor();
	mA->DrawNoColor();
    glEnd();
}

void Patch::DrawNormal()
{
    glColor3f(0, 0, 1);

	Point p = scalarMultiply(mPatchNormal, 10).Translate(mCenterPoint);

	glLineWidth(5);
	glBegin(GL_LINES);
	mCenterPoint.DrawNoColor();
	p.DrawNoColor();
	glEnd();
}

float Patch::Intersect(Vector v, Point o)
{
    // Check if vector is parallel to plane (no intercept)
    if (dotProduct(v, mPatchNormal) == 0)
    {
        return -1;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = 0;
    distance = dotProduct(Vector(*mA, o), mPatchNormal) / dotProduct(v, mPatchNormal);

    // From the distance, calculate the intersect point
    Point intersect = scalarMultiply(v, distance).Translate(o);

    // Test to see if the point is inside the rectangle
    Vector CI(intersect, *mC);
    Vector BC(*mB, *mC);
    Vector CD(*mD, *mC);

    if (((0 <= dotProduct(CI, BC)) &&
        (dotProduct(CI, BC) < dotProduct(BC, BC)) &&
        (0 <= dotProduct(CI, CD)) &&
        (dotProduct(CI, CD) < dotProduct(CD, CD))))
    {
    }
    else
    {
        distance = 0;
    }

    return distance;
}

bool Patch::Contains(Point p) const
{
    // Test to see if the point is inside the rectangle
    Vector CI(p, *mC);
    Vector BC(*mB, *mC);
    Vector CD(*mD, *mC);

    return !(((0 <= dotProduct(CI, BC)) &&
        (dotProduct(CI, BC) < dotProduct(BC, BC)) &&
        (0 <= dotProduct(CI, CD)) &&
        (dotProduct(CI, CD) < dotProduct(CD, CD))));
}

bool Patch::IsFacing(const Patch *other) const
{
	if (this == other)
	{
		return false;
	}

	Vector v21(mCenterPoint, other->mCenterPoint);
	Vector v12(other->mCenterPoint, mCenterPoint);
	normalize(v12);
	normalize(v21);

	float dp1 = dotProduct(v12, mPatchNormal);
	float dp2 = dotProduct(v21, other->mPatchNormal);
	float dp = dotProduct(mPatchNormal, other->mPatchNormal);

	if ( !(
				((dp == -1) && (dp1 < 0 || dp2 < 0))
			 || ((dp == 0) && (dp1 < 0))
			 || (dp == 1)
			 || (dp < 0 && dp > -1 && (dp1 < 0 || dp2 < 0))
			 || (dp1 < 0 || dp2 < 0)
	   )  )
	{
		return true;
	}
	return false;
}

void Patch::AddViewablePatch(Patch *patch)
{
    // Add the patch to the line of sight vector
    mViewablePatches->push_back(patch);

    // Add a form factor for this patch in parallel
    mFormFactors->push_back(0);
}

void Patch::RemoveViewablePatch(Patch *patch)
{
    std::vector<Patch*>::iterator iter1 = mViewablePatches->begin();

    for (; iter1 != mViewablePatches->end(); ++iter1)
    {
        // Remove the viewable patch, and its form factor
        if (*iter1 == patch)
        {
            iter1 = mViewablePatches->erase(iter1);
            break;
        }
    }

    // Add a form factor for this patch in parallel
    mFormFactors->pop_back();
}

void Patch::UpdateFormFactor(int index, float formFactor)
{
    mFormFactors->at(index) += formFactor;
}

void Patch::UpdateIncidence()
{
    // Set incidence to zero so that the last iteration is not added
    // in again.
    mIncidence = Color();

    // For every viewable patch
    for (unsigned int index(0); index < mViewablePatches->size(); ++index)
    {
        // Update the patch's incident light
        mIncidence += mViewablePatches->at(index)->mExidence *
            mFormFactors->at(index);
    }
}

void Patch::UpdateExidence()
{
#ifdef COLOR_BLENDING
    mExidence = mIncidence * (mColor * mReflectance) + mEmission;
#else
    mExidence = mIncidence * (mReflectance) + mEmission;
#endif
}

void Patch::UpdateCornerColors()
{
    mA->UpdateColor((mColor * mExidence));
    mB->UpdateColor((mColor * mExidence));
    mC->UpdateColor((mColor * mExidence));
    mD->UpdateColor((mColor * mExidence));
}

}   // namespace Radiosity

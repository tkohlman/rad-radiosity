///
/// @file Rectangle.cpp
///
/// @author	Thomas Kohlman
/// @date 30 December 2011
///
/// @description
/// 	Rectangle shape representation.
///

#include "Rectangle.h"
using namespace std;

namespace Radiosity {

// Rectangle
Rectangle::Rectangle(Point a, Point b, Point c, Point d, Color color,
    float emit) :
    Shape(color), _a(a), _b(b), _c(c), _d(d), emission(emit), mPatches(NULL) {

    // calculate the normal vector
    Vector v1(b, a);
    Vector v2(d, a);

    _normal = crossProduct(v2, v1); // cross product
}

// ~Rectangle
Rectangle::~Rectangle() {
}

// Intersect
Point* Rectangle::Intersect(Vector v, Point o) {

    // Check if vector is parallel to plane (no intercept)
    if (dotProduct(v, _normal) == 0)
    {
        return NULL;
    }

    // Find the distance from the ray origin to the intersect point
    float distance = dotProduct(Vector(_a, o), _normal) / dotProduct(v, _normal);

    // From the distance, calculate the intersect point
    Point *intersect = new Point(scalarMultiply(v, distance).Translate(o));

    // Test to see if the point is inside the rectangle
    Vector v_test(*intersect, _c);
    Vector v1_test(_b, _c);
    Vector v2_test(_c, _d);

    if ( (0 <= dotProduct(v_test, v1_test)) &&
         (dotProduct(v_test, v1_test) < dotProduct(v1_test, v1_test)) &&
         (0 <= dotProduct(v_test, v2_test)) &&
         (dotProduct(v_test, v2_test) < dotProduct(v2_test, v2_test)))
    {
        return intersect;
    }
    else
    {
        // does not intersect plane within the rectangle
        return NULL;
    }
}

void Rectangle::Subdivide(float patchSize)
{

	if (mPatches == NULL)
	{
		mPatches = new vector< Patch* >();

		// Calculate the number of patches along one axis
		float distance_i = _a.DistanceTo(_b);
		float dimension_i = distance_i / patchSize;
		int size_i = int(dimension_i);
		float remainder_i = dimension_i - size_i;

		if (remainder_i > 0) {
			++size_i;
		}

		// Calculate the number of patches along the other axis
		float distance_j = _a.DistanceTo(_d);
		float dimension_j = distance_j / patchSize;
		int size_j = int(dimension_j);
		float remainder_j = dimension_j - size_j;

		if (remainder_j > 0) {
			++size_j;
		}

		// Create a two-dimensional vector to hold points
		vector< vector<Point*> > points(size_i + 1, vector<Point*>(size_j + 1,
			(Point*)NULL));



		Vector AB(_b, _a);
		Vector AD(_d, _a);
		float len_AB = _b.DistanceTo(_a);
		float len_AD = _d.DistanceTo(_a);

		AB.Normalize();
		AD.Normalize();

		Point *p1;

		// Create the starting point
		p1 = new Point(_a);

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
					p3 = new Point(scalarMultiply(AB, patchSize).Translate(*p2));
				}

				// add p3 to the list
				points.at(i+1).at(j) = p3;

				// Update p2
				p2 = p3;
			}

			// Update p1
			if (j == size_j - 1) {
				p1 = new Point(scalarMultiply(AD, len_AD).Translate(_a));
			} else {
				p1 = new Point(scalarMultiply(AD, patchSize).Translate(*p1));
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
				Patch *p = new Patch(A, B, C, D, GetColor(), emission);
				mPatches->push_back(p);
			}
		}
	}
}

// A
Point Rectangle::A() const {
    return _a;
}

// B
Point Rectangle::B() const {
    return _b;
}

// C
Point Rectangle::C() const {
    return _c;
}

// D
Point Rectangle::D() const {
    return _d;
}



}   // namespace Radiosity





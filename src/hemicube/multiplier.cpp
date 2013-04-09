
#include "multiplier.h"
#include "vector.h"

namespace Radiosity
{

Multiplier::Multiplier(const Point &centerPoint,
                       const Point &startingPoint,
                       const Vector &patchNormal,
                       const Vector &faceNormal,
                       Vector row,
                       Vector col,
                       int numRows,
                       int numCols):
    m_height(numRows),
    m_width(numCols),
    m_sum(0)
{
    m_weights = new std::vector<float>();

    // This algorithm fires rays through the surface pixels of the hemicube.
    // The pixel width is defined by 1/N.
    float dp = 1.0 / 25.0;

    // Make sure the row and column vectors are normalized. Then weight them
    // by dp.
    Radiosity::normalize(row);
    Radiosity::normalize(col);
    row = scalarMultiply(row, dp);
    col = scalarMultiply(col, dp);

    // We will be looping in two directions.The outer loop determines the
    // row index of the multiplier table. The inner loop determines the column
    // index of the multiplier table.

    Point e = scalarMultiply(add(row, col), 0.5).Translate(startingPoint);

    for (int r(0); r < numRows; ++r)
    {
        Point f = e;
        for (int c(0); c < numCols; ++c)
        {
            // Create the ray, which depends on the face you are dealing with.
            Vector ray(f, centerPoint);
            Radiosity::normalize(ray);

            // Compensate for the hemicube's shape. This involves multiplying
            // the value by the dot product between the face normal and the
            // ray.
            float value = dotProduct(ray, faceNormal);

            // Apply Lambert's cosine law, which says that the apparent
            // brightness of a surface is proportional to the cosine of the
            // angle between the surface normal and the direction of light.
            value *= dotProduct(ray, patchNormal);

            // Set the value in the multiplier map
            m_weights->push_back(value);
            m_sum += value;

            // Update f
            f = col.Translate(f);
        }

        // Update e
        e = row.Translate(e);
    }
}

void Multiplier::normalize(float normalization_factor)
{
    for (unsigned int index = 0; index < m_weights->size(); ++index)
    {
        m_weights->at(index) /= normalization_factor;
    }

    m_sum /= normalization_factor;
}

float Multiplier::weight_at(int row, int column)
{
    return m_weights->at(row * m_width + column);
}

}   // namespace Radiosity

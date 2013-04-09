#ifndef MULTIPLIER_H_INCLUDED
#define MULTIPLIER_H_INCLUDED

#include <vector>

namespace Radiosity
{

class Point;
class Vector;

class Multiplier
{
public:

    Multiplier(const Point &centerPoint,
               const Point &startingPoint,
               const Vector &patchNormal,
               const Vector &faceNormal,
               Vector row,
               Vector col,
               int numRows,
               int numCols);

    void normalize(float normalization_factor);

    float weight_at(int row, int column);

    unsigned int height() const { return m_height; };
    unsigned int width() const { return m_width; };
    float sum() const { return m_sum; };

private:

    unsigned int m_height;
    unsigned int m_width;

    float m_sum;

    std::vector<float> *m_weights;
};

}   // namespace Radiosity

#endif // MULTIPLIER_H_INCLUDED

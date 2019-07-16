#include "geoshape/Box.h"

namespace gs
{

Box::Box()
{
    m_bounding = sm::cube(1, 1, 1);
}

Box::Box(const sm::cube& cube)
{
    m_bounding = cube;
}

std::unique_ptr<Shape> Box::Clone() const
{
    return std::make_unique<Box>(m_bounding);
}

}
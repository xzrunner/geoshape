#pragma once

#include "geoshape/Shape.h"

#include <SM_Cube.h>

namespace gs
{

class Shape3D : public Shape
{
public:
    Shape3D() {}

//    virtual bool IsContain(const sm::vec3& pos) const = 0;

protected:
    sm::cube m_bounding;

    RTTR_ENABLE(Shape)

}; // Shape3D

}
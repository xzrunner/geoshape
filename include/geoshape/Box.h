#pragma once

#include "geoshape/Shape3D.h"

namespace gs
{

class Box : public Shape3D
{
public:
    Box();
    Box(const sm::cube& cube);

    virtual std::unique_ptr<Shape3D> Clone() const override;

    const sm::cube& GetCube() const { return m_bounding; }
    void SetCube(const sm::cube& cube) { m_bounding = cube; }

    RTTR_ENABLE(Shape3D)

}; // Box

}
#pragma once

#include "geoshape/Shape3D.h"

namespace gs
{

class Point3D : public Shape3D
{
public:
    Point3D();
    Point3D(const sm::vec3& pos);

    virtual std::unique_ptr<Shape3D> Clone() const override;

    auto& GetPos() const { return m_pos; }
    void SetPos(const sm::vec3& pos);

private:
    void BuildBounding();

private:
    sm::vec3 m_pos;

#ifndef RTTR_DISABLE
    RTTR_ENABLE(Shape3D)
#endif // RTTR_DISABLE

}; // Point3D

}
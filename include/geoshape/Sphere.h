#pragma once

#include "geoshape/Shape3D.h"

namespace n3 { class CompTransform; }

namespace gs
{

class Sphere : public Shape3D
{
public:
    Sphere();
    Sphere(const sm::vec3& center, float radius);

    virtual std::unique_ptr<Shape3D> Clone() const override;

    auto& GetCenter() const { return m_center; }
    float GetRadius() const { return m_radius; }

private:
    sm::vec3 m_center;
    float    m_radius = 1;

    RTTR_ENABLE(Shape3D)

}; // Sphere

}
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
    void  SetCenter(const sm::vec3& center) { m_center = center; }

    float GetRadius() const { return m_radius; }
    void  SetRadius(float radius) { m_radius = radius; }

private:
    void BuildBounding();

private:
    sm::vec3 m_center;
    float    m_radius = 1;

    RTTR_ENABLE(Shape3D)

}; // Sphere

}
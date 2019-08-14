#include "geoshape/Sphere.h"

namespace gs
{

Sphere::Sphere()
{
    BuildBounding();
}

Sphere::Sphere(const sm::vec3& center, float radius)
    : m_center(center)
    , m_radius(radius)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> Sphere::Clone() const
{
    return std::make_unique<Sphere>(m_center, m_radius);
}

void Sphere::BuildBounding()
{
    const float r = m_radius * 2;
    m_bounding = sm::cube(m_center, r, r, r);
}

}
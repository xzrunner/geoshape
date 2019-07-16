#include "geoshape/Sphere.h"

namespace gs
{

Sphere::Sphere()
{
    const float l = m_radius * 2;
    m_bounding = sm::cube(m_center, l, l, l);
}

Sphere::Sphere(const sm::vec3& center, float radius)
    : m_center(center)
    , m_radius(radius)
{
    const float l = radius * 2;
    m_bounding = sm::cube(center, l, l, l);
}

std::unique_ptr<Shape> Sphere::Clone() const
{
    return std::make_unique<Sphere>(m_center, m_radius);
}

}
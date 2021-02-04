#include "geoshape/Polygon3D.h"

#ifndef RTTR_DISABLE
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polygon3D>("gs_polygon3d")
	.constructor<>()
	.constructor<const std::vector<sm::vec3>&>()
	.property("vertices", &gs::Polygon3D::GetVertices, &gs::Polygon3D::SetVertices)
;

}
#endif // RTTR_DISABLE

namespace gs
{

Polygon3D::Polygon3D()
{
    BuildBounding();
}

Polygon3D::Polygon3D(const std::vector<sm::vec3>& vertices)
    : m_vertices(vertices)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> Polygon3D::Clone() const
{
    return std::make_unique<Polygon3D>(m_vertices);
}

void Polygon3D::SetVertices(const std::vector<sm::vec3>& vertices)
{
    m_vertices = vertices;

    BuildBounding();
}

void Polygon3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    for (auto& v : m_vertices) {
        m_bounding.Combine(v);
    }
}

}
#include "geoshape/Polyline3D.h"

#ifndef RTTR_DISABLE
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polyline3D>("gs_polyline3d")
	.constructor<>()
	.constructor<const std::vector<sm::vec3>&, bool>()
	.property("vertices", &gs::Polyline3D::GetVertices, &gs::Polyline3D::SetVertices)
    .property("closed", &gs::Polyline3D::GetClosed, &gs::Polyline3D::SetClosed)
;

}
#endif // RTTR_DISABLE

namespace gs
{

Polyline3D::Polyline3D()
{
    BuildBounding();
}

Polyline3D::Polyline3D(const std::vector<sm::vec3>& vertices, bool is_closed)
    : m_vertices(vertices)
    , m_is_closed(is_closed)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> Polyline3D::Clone() const
{
    return std::make_unique<Polyline3D>(m_vertices, m_is_closed);
}

void Polyline3D::SetVertices(const std::vector<sm::vec3>& vertices)
{
    m_vertices = vertices;

    BuildBounding();
}

void Polyline3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    for (auto& v : m_vertices) {
        m_bounding.Combine(v);
    }
}

}
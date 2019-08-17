#include "geoshape/PointSet3D.h"

namespace gs
{

PointSet3D::PointSet3D()
{
    BuildBounding();
}

PointSet3D::PointSet3D(const std::vector<sm::vec3>& vertices)
    : m_vertices(vertices)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> PointSet3D::Clone() const
{
    return std::make_unique<PointSet3D>(m_vertices);
}

void PointSet3D::SetVertices(const std::vector<sm::vec3>& vertices)
{
    m_vertices = vertices;

    BuildBounding();
}

void PointSet3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    for (auto& v : m_vertices) {
        m_bounding.Combine(v);
    }
}

}
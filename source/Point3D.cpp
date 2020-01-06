#include "geoshape/Point3D.h"

RTTR_REGISTRATION
{

rttr::registration::class_<gs::Point3D>("gs_point3d")
	.constructor<>()
	.constructor<const sm::vec3&>()
	.property("pos", &gs::Point3D::GetPos, &gs::Point3D::SetPos)
;

}

namespace gs
{

Point3D::Point3D()
{
    BuildBounding();
}

Point3D::Point3D(const sm::vec3& pos)
    : m_pos(pos)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> Point3D::Clone() const
{
    return std::make_unique<Point3D>(m_pos);
}

void Point3D::SetPos(const sm::vec3& pos)
{
    m_pos = pos;

    BuildBounding();
}

void Point3D::BuildBounding()
{
    m_bounding = sm::cube(m_pos, 0.1f, 0.1f, 0.1f);
}

}
#include "geoshape/Line3D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef RTTR_DISABLE
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Line3D>("gs_line3d")
	.constructor<>()
	.constructor<const sm::vec3&, const sm::vec3&>()
	.property("start", &gs::Line3D::GetStart, &gs::Line3D::SetStart)
    .property("end", &gs::Line3D::GetEnd, &gs::Line3D::SetEnd)
;

}
#endif // RTTR_DISABLE

namespace gs
{

Line3D::Line3D(const sm::vec3& start, const sm::vec3& end)
	: m_start(start)
    , m_end(end)
{
	BuildBounding();
}

std::unique_ptr<Shape3D> Line3D::Clone() const
{
	return std::make_unique<Line3D>(m_start, m_end);
}

void Line3D::SetStart(const sm::vec3& start)
{
	m_start = start;
	BuildBounding();
}

void Line3D::SetEnd(const sm::vec3& end)
{
	m_end = end;
	BuildBounding();
}

void Line3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    m_bounding.Combine(m_start);
    m_bounding.Combine(m_end);
}

}
#include "geoshape/Polyline2D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef RTTR_DISABLE
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polyline2D>("gs_polyline2d")
	.constructor<>()
	.constructor<const std::vector<sm::vec2>&>()
	.property("vertices", &gs::Polyline2D::GetVertices, &gs::Polyline2D::SetVertices)
;

}
#endif // RTTR_DISABLE

namespace gs
{

Polyline2D::Polyline2D(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, false)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape2D> Polyline2D::Clone() const
{
	return std::make_unique<Polyline2D>(m_impl.GetVertices());
}

bool Polyline2D::IsContain(const sm::vec2& pos) const
{
	return m_impl.IsContain(pos);
}

bool Polyline2D::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Polyline2D::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
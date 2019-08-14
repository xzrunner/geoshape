#include "geoshape/Polygon.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

RTTR_REGISTRATION
{
	rttr::registration::class_<gs::Polygon>("gs_polygon")
		.constructor<>()
		.constructor<const std::vector<sm::vec2>&>()
		.property("vertices", &gs::Polygon::GetVertices, &gs::Polygon::SetVertices)
	;
}

namespace gs
{

Polygon::Polygon(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, true)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape2D> Polygon::Clone() const
{
	return std::make_unique<Polygon>(m_impl.GetVertices());
}

bool Polygon::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_area(pos, m_impl.GetVertices());
}

bool Polygon::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Polygon::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
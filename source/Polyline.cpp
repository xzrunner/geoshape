#include "geoshape/Polyline.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

RTTR_REGISTRATION
{
	rttr::registration::class_<gs::Polyline>("gs_polyline")
		.constructor<>()
		.constructor<const std::vector<sm::vec2>&>()
		.property("vertices", &gs::Polyline::GetVertices, &gs::Polyline::SetVertices)
	;
}

namespace gs
{

Polyline::Polyline(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, false)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape2D> Polyline::Clone() const
{
	return std::make_unique<Polyline>(m_impl.GetVertices());
}

bool Polyline::IsContain(const sm::vec2& pos) const
{
	return m_impl.IsContain(pos);
}

bool Polyline::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Polyline::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
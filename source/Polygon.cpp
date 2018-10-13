#include "geoshape/Polygon.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

namespace gs
{

IMPLEMENT_CHILD_CLASS_INFO(Shape, Polygon, Polygon)

Polygon::Polygon(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, true)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape> Polygon::Clone() const
{
	return std::make_unique<Polygon>(m_impl.GetVertices());
}

bool Polygon::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_area(pos, m_impl.GetVertices());
}

bool Polygon::IsIntersect(const sm::rect& rect) const
{
	return sm::is_rect_intersect_polygon(rect, m_impl.GetVertices());
}

void Polygon::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
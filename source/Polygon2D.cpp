#include "geoshape/Polygon2D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>
#include <SM_Triangulation.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polygon2D>("gs_polygon2d")
	.constructor<>()
	.constructor<const std::vector<sm::vec2>&>()
	.property("vertices", &gs::Polygon2D::GetVertices, &gs::Polygon2D::SetVertices)
;

}
#endif // NO_RTTR

namespace gs
{

Polygon2D::Polygon2D(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, true)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape2D> Polygon2D::Clone() const
{
	return std::make_unique<Polygon2D>(m_impl.GetVertices());
}

bool Polygon2D::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_area(pos, m_impl.GetVertices());
}

bool Polygon2D::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Polygon2D::Translate(float dx, float dy)
{
	m_impl.Translate(sm::vec2(dx, dy));

	m_tris.clear();
}

void Polygon2D::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();

	m_tris.clear();
}

const std::vector<sm::vec2>& Polygon2D::GetTris() const 
{ 
	if (m_tris.empty()) {
		BuildTriangles();
	}
	return m_tris; 
}

void Polygon2D::BuildTriangles() const
{
	m_tris.clear();
	std::vector<std::vector<sm::vec2>> holes;
	sm::triangulate_holes(m_impl.GetVertices(), holes, m_tris);
}

}
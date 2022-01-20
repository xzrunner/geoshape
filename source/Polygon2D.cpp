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

Polygon2D::Polygon2D(const std::vector<sm::vec2>& border)
	: m_border(border, true)
{
	m_bounding = m_border.GetBounding();
}

Polygon2D::Polygon2D(const std::vector<sm::vec2>& border, const std::vector<std::vector<sm::vec2>>& holes)
	: m_border(border, true)
	, m_holes(holes)
{
	m_bounding = m_border.GetBounding();
}

std::unique_ptr<Shape2D> Polygon2D::Clone() const
{
	return std::make_unique<Polygon2D>(m_border.GetVertices(), m_holes);
}

bool Polygon2D::IsContain(const sm::vec2& pos) const
{
	if (!sm::is_point_in_area(pos, m_border.GetVertices())) {
		return false;
	}

	for (auto& hold : m_holes) {
		if (sm::is_point_in_area(pos, hold)) {
			return false;
		}
	}

	return true;
}

bool Polygon2D::IsIntersect(const sm::rect& rect) const
{
	return m_border.IsIntersect(rect);
}

void Polygon2D::Translate(float dx, float dy)
{
	sm::vec2 d(dx, dy);

	m_border.Translate(d);

	for (auto& hole : m_holes) {
		for (auto& p : hole) {
			p += d;
		}
	}

	m_tris.clear();
}

void Polygon2D::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_border.SetVertices(vertices);
	m_bounding = m_border.GetBounding();

	m_tris.clear();
}

void Polygon2D::AddHole(const std::vector<sm::vec2>& hole)
{
	m_holes.push_back(hole);

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

	sm::triangulate_holes(m_border.GetVertices(), m_holes, m_tris);
}

}
#include "geoshape/Triangles.h"

#include <SM_Calc.h>
#include <SM_Triangulation.h>

namespace gs
{

Triangles::Triangles(const std::vector<sm::vec2>& border)
	: m_border(border)
{
	Update();
}

std::unique_ptr<Shape2D> Triangles::Clone() const
{
	return std::make_unique<Triangles>(m_border);
}

bool Triangles::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_area(pos, m_border);
}

bool Triangles::IsIntersect(const sm::rect& rect) const
{
	return sm::is_rect_intersect_polygon(rect, m_border);
}

void Triangles::Translate(float dx, float dy)
{
	auto offset = sm::vec2(dx, dy);
	for (auto& vert : m_border) {
		vert += offset;
	}
	Update();
}

void Triangles::SetBorder(const std::vector<sm::vec2>& border)
{
	m_border = border;
	Update();
}

void Triangles::Update()
{
	UpdateBounding();
	BuildTriangles();
}

void Triangles::UpdateBounding()
{
	m_bounding.MakeEmpty();
	for (auto& v : m_border) {
		m_bounding.Combine(v);
	}
}

void Triangles::BuildTriangles()
{
	m_tris.clear();
	std::vector<std::vector<sm::vec2>> holes;
	sm::triangulate_holes(m_border, holes, m_tris);
}

}
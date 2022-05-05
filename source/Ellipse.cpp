#include "geoshape/Ellipse.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#include <cmath>

namespace gs
{

Ellipse::Ellipse(const sm::vec2& center, float rx, float ry)
	: m_center(center)
	, m_radius_x(rx)
	, m_radius_y(ry)
{
	m_impl.SetClosed(true);
	Reset();
}

std::unique_ptr<Shape2D> Ellipse::Clone() const
{
	return std::make_unique<Ellipse>(m_center, m_radius_x, m_radius_y);
}

bool Ellipse::IsContain(const sm::vec2& pos) const
{
	const float dx = pos.x - m_center.x;
	const float dy = pos.y - m_center.y;
	return (dx * dx) / (m_radius_x * m_radius_x) + (dy * dy) / (m_radius_y * m_radius_y) < 1;
}

bool Ellipse::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Ellipse::Translate(float dx, float dy)
{
	SetCenter(m_center + sm::vec2(dx, dy));
}

void Ellipse::SetCenter(const sm::vec2& center)
{
	if (m_center == center) {
		return;
	}

	m_center = center;
	Reset();
}

void Ellipse::GetRadius(float& radius_x, float& radius_y) const
{
	radius_x = m_radius_x;
	radius_y = m_radius_y;
}

void Ellipse::SetRadius(float radius_x, float radius_y)
{
	if (m_radius_x == radius_x &&
		m_radius_y == radius_y) {
		return;
	}

	m_radius_x = radius_x;
	m_radius_y = radius_y;
	Reset();
}

std::vector<sm::vec2> Ellipse::TransToPolyline() const
{
	const int MAX_NUM = 32;

	const float d_angle = SM_TWO_PI / MAX_NUM;

	std::vector<sm::vec2> polyline;
	polyline.reserve(MAX_NUM);

	for (int i = 0; i < MAX_NUM; ++i)
	{
		float a = i * d_angle;
		const float x = m_center.x + m_radius_x * std::cosf(a);
		const float y = m_center.y + m_radius_y * std::sinf(a);
		polyline.push_back(sm::vec2(x, y));
	}

	return polyline;
}

void Ellipse::Reset()
{
	auto polyline = TransToPolyline();
	m_impl.SetVertices(polyline);

	m_bounding = m_impl.GetBounding();
}

}
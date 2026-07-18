#include "geoshape/Ellipse.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#include <cmath>

namespace gs
{

Ellipse::Ellipse(const sm::vec2& center, float rx, float ry, float rotation)
	: m_center(center)
	, m_radius_x(rx)
	, m_radius_y(ry)
	, m_rotation(rotation)
{
	m_impl.SetClosed(true);
	Reset();
}

std::unique_ptr<Shape2D> Ellipse::Clone() const
{
	return std::make_unique<Ellipse>(m_center, m_radius_x, m_radius_y, m_rotation);
}

bool Ellipse::IsContain(const sm::vec2& pos) const
{
	// Bring pos into the ellipse's local (un-rotated) frame first, then apply
	// the axis-aligned containment test.
	const float c = std::cosf(-m_rotation);
	const float s = std::sinf(-m_rotation);
	const float ox = pos.x - m_center.x;
	const float oy = pos.y - m_center.y;
	const float dx = ox * c - oy * s;
	const float dy = ox * s + oy * c;
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

void Ellipse::SetRotation(float rotation)
{
	if (m_rotation == rotation) {
		return;
	}

	m_rotation = rotation;
	Reset();
}

std::vector<sm::vec2> Ellipse::TransToPolyline() const
{
	const int MAX_NUM = 32;

	const float d_angle = SM_TWO_PI / MAX_NUM;

	// Rotate each axis-aligned sample by m_rotation about the centre.
	const float cr = std::cosf(m_rotation);
	const float sr = std::sinf(m_rotation);

	std::vector<sm::vec2> polyline;
	polyline.reserve(MAX_NUM);

	for (int i = 0; i < MAX_NUM; ++i)
	{
		float a = i * d_angle;
		const float ex = m_radius_x * std::cosf(a);
		const float ey = m_radius_y * std::sinf(a);
		const float x = m_center.x + ex * cr - ey * sr;
		const float y = m_center.y + ex * sr + ey * cr;
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
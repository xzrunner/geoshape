#include "geoshape/Arc.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#include <cmath>

namespace gs
{

Arc::Arc(const sm::vec2& center, float radius, float start_angle, float end_angle)
	: m_center(center)
	, m_radius(radius)
	, m_start_angle(start_angle)
	, m_end_angle(end_angle)
{
	m_impl.SetClosed(false);
	Reset();
}

std::unique_ptr<Shape2D> Arc::Clone() const
{
	return std::make_unique<Arc>(m_center, m_radius, m_start_angle, m_end_angle);
}

//bool Arc::IsContain(const sm::vec2& pos) const
//{
//	float s = m_start_angle;
//	float e = m_end_angle;
//	if (e < s) {
//		e += SM_TWO_PI;
//	}
//
//	float angle = sm::get_line_angle(m_center, pos);
//	if (angle < s || angle > e) {
//		return false;
//	}
//
//	float d = sm::dis_pos_to_pos(m_center, pos);
//	return fabs(d - m_radius) < NODE_QUERY_RADIUS;
//}

bool Arc::IsContain(const sm::vec2& pos) const
{
	sm::vec2 start = m_center + sm::rotate_vector(sm::vec2(m_radius, 0), m_start_angle);
	sm::vec2 end   = m_center + sm::rotate_vector(sm::vec2(m_radius, 0), m_end_angle);
	return sm::dis_pos_to_pos(pos, m_center) < NODE_QUERY_RADIUS
		|| sm::dis_pos_to_pos(pos, start) < NODE_QUERY_RADIUS
		|| sm::dis_pos_to_pos(pos, end) < NODE_QUERY_RADIUS;
}

bool Arc::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Arc::Translate(float dx, float dy)
{
	SetCenter(m_center + sm::vec2(dx, dy));
}

void Arc::SetCenter(const sm::vec2& center)
{
	m_center = center;
	Reset();
}

void Arc::SetRadius(float radius)
{
	m_radius = radius;
	Reset();
}

void Arc::GetAngles(float& start_angle, float& end_angle) const
{
	start_angle = m_start_angle;
	end_angle = m_end_angle;
}

void Arc::SetAngles(float start_angle, float end_angle)
{
	if (m_start_angle == start_angle &&
		m_end_angle == end_angle) {
		return;
	}

	m_start_angle = fmod(start_angle, SM_TWO_PI);
	m_end_angle = fmod(end_angle, SM_TWO_PI);

	Reset();
}

std::vector<sm::vec2> Arc::TransToPolyline() const
{
	float s = m_start_angle;
	float e = m_end_angle;
	if (e < s) {
		e += SM_TWO_PI;
	}

	const int MAX_NUM = 32;
	const int num = std::ceil((e - s) / SM_TWO_PI * MAX_NUM);
	const float d_angle = SM_TWO_PI / MAX_NUM;

	std::vector<sm::vec2> polyline;
	polyline.reserve(num + 1);
	for (int i = 0; i < num; ++i)
	{
		float a = m_start_angle + i * d_angle;
		float x = m_center.x + m_radius * std::cosf(a);
		float y = m_center.y + m_radius * std::sinf(a);
		polyline.push_back(sm::vec2(x, y));
	}

	float x = m_center.x + m_radius * std::cosf(m_end_angle);
	float y = m_center.y + m_radius * std::sinf(m_end_angle);
	polyline.push_back(sm::vec2(x, y));

	return polyline;
}

void Arc::Reset()
{
	auto polyline = TransToPolyline();
	m_impl.SetVertices(polyline);

	m_bounding = m_impl.GetBounding();
}

}
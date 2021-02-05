#include "geoshape/Circle.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Circle>("gs_circle")
	.constructor<>()
	.constructor<const sm::vec2&, float>()
	.property("center", &gs::Circle::GetCenter, &gs::Circle::SetCenter)
	.property("radius", &gs::Circle::GetRadius, &gs::Circle::SetRadius)
;

}
#endif // NO_RTTR

namespace gs
{

Circle::Circle(const sm::vec2& center, float radius)
	: m_center(center)
	, m_radius(radius)
{
	UpdateBounding();
}

std::unique_ptr<Shape2D> Circle::Clone() const
{
	return std::make_unique<Circle>(m_center, m_radius);
}

bool Circle::IsContain(const sm::vec2& pos) const
{
	return sm::dis_pos_to_pos(m_center, pos) < m_radius;
}

bool Circle::IsIntersect(const sm::rect& rect) const
{
	sm::vec2 r_center = rect.Center();
	float center_dis = sm::dis_pos_to_pos(r_center, m_center);
	float r_radius = sm::dis_pos_to_pos(r_center, sm::vec2(rect.xmax, rect.ymax));
	if (center_dis > m_radius + r_radius) {
		return false;
	}

	if (sm::is_point_in_circle(sm::vec2(rect.xmin, rect.ymin), m_center, m_radius)) return true;
	if (sm::is_point_in_circle(sm::vec2(rect.xmax, rect.ymin), m_center, m_radius)) return true;
	if (sm::is_point_in_circle(sm::vec2(rect.xmax, rect.ymax), m_center, m_radius)) return true;
	if (sm::is_point_in_circle(sm::vec2(rect.xmin, rect.ymax), m_center, m_radius)) return true;
	if (sm::is_point_in_rect(m_center, rect)) return true;

	if (m_center.x > rect.xmin && m_center.x < rect.xmax) {
		if (center_dis < rect.ymax - r_center.y + m_radius) {
			return true;
		}
	}
	if (m_center.y > rect.ymin && m_center.y < rect.ymax) {
		if (center_dis < rect.xmax - r_center.x + m_radius) {
			return true;
		}
	}

	return false;
}

void Circle::SetCenter(const sm::vec2& center)
{
	m_center = center;
	UpdateBounding();
}

void Circle::SetRadius(float radius)
{
	m_radius = radius;
	UpdateBounding();
}

void Circle::UpdateBounding()
{
	m_bounding = sm::rect(m_center, m_radius * 2, m_radius * 2);
}

}
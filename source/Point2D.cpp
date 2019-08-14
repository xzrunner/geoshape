#include "geoshape/Point2D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

RTTR_REGISTRATION
{
	rttr::registration::class_<gs::Point2D>("gs_point2d")
		.constructor<>()
		.constructor<const sm::vec2&>()
		.property("pos", &gs::Point2D::GetPos, &gs::Point2D::SetPos)
	;
}

namespace gs
{

Point2D::Point2D(const sm::vec2& pos)
	: m_pos(pos)
{
	UpdateBounding();
}

std::unique_ptr<Shape2D> Point2D::Clone() const
{
	return std::make_unique<Point2D>(m_pos);
}

bool Point2D::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_rect(pos, m_bounding);
}

bool Point2D::IsIntersect(const sm::rect& rect) const
{
	return sm::is_rect_intersect_rect(rect, m_bounding);
}

void Point2D::SetPos(const sm::vec2& pos)
{
	m_pos = pos;
	UpdateBounding();
}

void Point2D::UpdateBounding()
{
	m_bounding.xmin = m_bounding.ymin = -NODE_QUERY_RADIUS;
	m_bounding.xmax = m_bounding.ymax =  NODE_QUERY_RADIUS;
}

}
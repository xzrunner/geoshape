#include "geoshape/Line2D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

RTTR_REGISTRATION
{

rttr::registration::class_<gs::Line2D>("gs_line2d")
	.constructor<>()
	.constructor<const sm::vec2&, const sm::vec2&>()
	.property("start", &gs::Line2D::GetStart, &gs::Line2D::SetStart)
    .property("end", &gs::Line2D::GetEnd, &gs::Line2D::SetEnd)
;

}

namespace gs
{

Line2D::Line2D(const sm::vec2& start, const sm::vec2& end)
	: m_start(start)
    , m_end(end)
{
	UpdateBounding();
}

std::unique_ptr<Shape2D> Line2D::Clone() const
{
	return std::make_unique<Line2D>(m_start, m_end);
}

bool Line2D::IsContain(const sm::vec2& pos) const
{
    sm::rect r(pos, SM_LARGE_EPSILON, SM_LARGE_EPSILON);
    return sm::is_rect_intersect_segment(r, m_start, m_end);
}

bool Line2D::IsIntersect(const sm::rect& rect) const
{
	return sm::is_rect_intersect_segment(rect, m_start, m_end);
}

void Line2D::SetStart(const sm::vec2& start)
{
	m_start = start;
	UpdateBounding();
}

void Line2D::SetEnd(const sm::vec2& end)
{
	m_end = end;
	UpdateBounding();
}

void Line2D::UpdateBounding()
{
    m_bounding.MakeEmpty();
    m_bounding.Combine(m_start);
    m_bounding.Combine(m_end);
}

}
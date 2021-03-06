#include "geoshape/Rect.h"
#include "geoshape/config.h"

#include <SM_Calc.h>
#include <primitive/Path.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Rect>("gs_rect")
	.constructor<>()
	.constructor<const sm::rect&>()
	.property("rect", &gs::Rect::GetRect, &gs::Rect::SetRect)
;

}
#endif // NO_RTTR

namespace gs
{

Rect::Rect(const sm::rect& rect)
{
	m_bounding = rect;
}

std::unique_ptr<Shape2D> Rect::Clone() const
{
	return std::make_unique<Rect>(m_bounding);
}

bool Rect::IsContain(const sm::vec2& pos) const
{
	return sm::is_point_in_rect(pos, m_bounding);
}

bool Rect::IsIntersect(const sm::rect& rect) const
{
	return sm::is_rect_intersect_rect(rect, m_bounding);
}

void Rect::Translate(float dx, float dy)
{
	m_bounding.xmin += dx;
	m_bounding.xmax += dx;
	m_bounding.ymin += dy;
	m_bounding.ymax += dy;
}

}
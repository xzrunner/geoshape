#include "geoshape/Rect.h"
#include "geoshape/config.h"

#include <SM_Calc.h>
#include <primitive/Path.h>

RTTR_REGISTRATION
{
	rttr::registration::class_<gs::Rect>("gs_rect")
		.constructor<>()
		.constructor<const sm::rect&>()
		.property("rect", &gs::Rect::GetRect, &gs::Rect::SetRect)
	;
}

namespace gs
{

Rect::Rect(const sm::rect& rect)
{
	m_bounding = rect;
}

std::unique_ptr<Shape> Rect::Clone() const
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

}
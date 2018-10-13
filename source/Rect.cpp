#include "geoshape/Rect.h"
#include "geoshape/config.h"

#include <SM_Calc.h>
#include <primitive/Path.h>

namespace gs
{

IMPLEMENT_CHILD_CLASS_INFO(Shape, Rect, Rect)

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

void Rect::Draw(render func) const
{
	prim::Path p;
	p.Rect({ m_bounding.xmin, m_bounding.ymin },
		m_bounding.Width(), m_bounding.Height() );
	auto& vertices = p.GetCurrPath();
	func(vertices.data(), vertices.size(), false, false);
//	func(vertices.data(), vertices.size() - 1, true, false);
}

}
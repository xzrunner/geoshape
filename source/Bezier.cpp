#include "geoshape/Bezier.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

namespace gs
{

IMPLEMENT_CHILD_CLASS_INFO(Shape, Bezier, Bezier)

Bezier::Bezier(const sm::vec2& v0, const sm::vec2& v1,
		       const sm::vec2& v2, const sm::vec2& v3)
{
	SetCtrlPos(v0, v1, v2, v3);
}

std::unique_ptr<Shape> Bezier::Clone() const
{
	sm::vec2 v0, v1, v2, v3;
	m_bezier.GetCtrlNodes(v0, v1, v2, v3);
	return std::make_unique<Bezier>(v0, v1, v2, v3);
}

bool Bezier::IsContain(const sm::vec2& pos) const
{
	sm::vec2 vs[4];
	m_bezier.GetCtrlNodes(vs[0], vs[1], vs[2], vs[3]);

	bool ret = false;
	for (auto& v : vs) {
		if (sm::dis_pos_to_pos(pos, v) < NODE_QUERY_RADIUS) {
			ret = true;
			break;
		}
	}
	return ret;
}

bool Bezier::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Bezier::SetCtrlPos(const sm::vec2& v0, const sm::vec2& v1,
	                    const sm::vec2& v2, const sm::vec2& v3)
{
	m_bezier.SetCtrlPos(v0, v1, v2, v3);
	std::vector<sm::vec2> vertices;
	m_bezier.TransToPolyline(vertices);
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
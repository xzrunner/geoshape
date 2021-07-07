#include "geoshape/Bezier.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Bezier>("gs_bezier")
	.constructor<>()
	.constructor<const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>&>()
	.property("ctrl_pos", &gs::Bezier::GetCtrlPos, &gs::Bezier::SetCtrlPos)
;

}
#endif // NO_RTTR

namespace gs
{

Bezier::Bezier(const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>& ctrl_nodes)
{
	SetCtrlPos(ctrl_nodes);
}

std::unique_ptr<Shape2D> Bezier::Clone() const
{
	return std::make_unique<Bezier>(m_bezier.GetCtrlNodes());
}

bool Bezier::IsContain(const sm::vec2& pos) const
{
	bool ret = false;
	for (auto& v : m_bezier.GetCtrlNodes())
	{
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

void Bezier::Translate(float dx, float dy)
{
	auto ctrl_nodes = GetCtrlPos();
	for (auto& pos : ctrl_nodes) {
		pos.x += dx;
		pos.y += dy;
	}
	SetCtrlPos(ctrl_nodes);
}

void Bezier::SetCtrlPos(const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>& ctrl_nodes)
{
	m_bezier.SetCtrlNodes(ctrl_nodes);
	std::vector<sm::vec2> vertices;
	m_bezier.TransToPolyline(vertices);
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

}
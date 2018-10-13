#include "geoshape/PolylineImpl.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

namespace gs
{

PolylineImpl::PolylineImpl(const std::vector<sm::vec2>& vertices,
	                       bool is_closed)
	: m_vertices(vertices)
	, m_is_closed(is_closed)
{
	UpdateBounding();
}

bool PolylineImpl::IsContain(const sm::vec2& pos) const
{
	if (m_vertices.empty()) {
		return false;
	}

	if (m_is_closed)
	{
		return sm::is_point_in_area(pos, m_vertices);
	}
	else
	{
		sm::rect rect(m_bounding);
		rect.xmin -= NODE_QUERY_RADIUS;
		rect.xmax += NODE_QUERY_RADIUS;
		rect.ymin -= NODE_QUERY_RADIUS;
		rect.ymax += NODE_QUERY_RADIUS;
		if (!sm::is_point_in_rect(pos, rect)) {
			return false;
		}

		float dis = sm::dis_pos_to_multi_pos(pos, m_vertices);
		if (dis < NODE_QUERY_RADIUS) {
			return true;
		}

		if (m_vertices.size() < 2) {
			return false;
		}
		for (int i = 0, n = m_vertices.size() - 1; i < n; ++i)
		{
			float dis = sm::dis_pos_to_seg(pos, m_vertices[i], m_vertices[i + 1]);
			if (dis < NODE_QUERY_RADIUS) {
				return true;
			}
		}

		return false;
	}
}

bool PolylineImpl::IsIntersect(const sm::rect& rect) const
{
	if (m_vertices.empty() || !sm::is_rect_intersect_rect(rect, m_bounding)) {
		return false;
	}

	for (auto& v : m_vertices) {
		if (sm::is_point_in_rect(v, rect))
			return true;
	}

	if (m_vertices.size() < 2) {
		return false;
	}
	for (int i = 0, n = m_vertices.size() - 1; i < n; ++i) {
		if (sm::is_rect_intersect_segment(rect, m_vertices[i], m_vertices[i + 1])) {
			return true;
		}
	}

	if (m_is_closed && sm::is_rect_intersect_segment(rect, m_vertices.front(), m_vertices.back())) {
		return true;
	}

	return false;
}

void PolylineImpl::Draw(render func, bool filling) const
{
	func(m_vertices.data(), m_vertices.size(), m_is_closed, filling);
}

void PolylineImpl::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_vertices = vertices;
	UpdateBounding();
}

void PolylineImpl::UpdateBounding()
{
	m_bounding.MakeEmpty();
	for (auto& v : m_vertices) {
		m_bounding.Combine(v);
	}
}

}
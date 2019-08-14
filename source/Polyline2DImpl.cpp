#include "geoshape/Polyline2DImpl.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

namespace gs
{

Polyline2DImpl::Polyline2DImpl(const std::vector<sm::vec2>& vertices,
	                       bool is_closed)
	: m_vertices(vertices)
	, m_is_closed(is_closed)
{
	UpdateBounding();
}

bool Polyline2DImpl::IsContain(const sm::vec2& pos) const
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

bool Polyline2DImpl::IsIntersect(const sm::rect& rect) const
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

void Polyline2DImpl::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_vertices = vertices;
	UpdateBounding();
}

bool Polyline2DImpl::AddVertex(int index, const sm::vec2& pos)
{
	if (index == m_vertices.size()) {
		m_vertices.push_back(pos);
		m_bounding.Combine(pos);
		return true;
	} else if (index >= 0 && index < static_cast<int>(m_vertices.size())) {
		m_vertices.insert(m_vertices.begin() + index, pos);
		m_bounding.Combine(pos);
		return true;
	} else {
		return false;
	}
}

bool Polyline2DImpl::RemoveVertex(const sm::vec2& pos)
{
	auto itr = m_vertices.begin();
	for ( ; itr != m_vertices.end(); ++itr)
	{
		if (*itr != pos) {
			continue;
		}
		m_vertices.erase(itr);
		if (IsPosOnBounding(pos)) {
			UpdateBounding();
		}
		return true;
	}
	return false;
}

bool Polyline2DImpl::ChangeVertex(const sm::vec2& from, const sm::vec2& to)
{
	int index = 0;
	for (int n = m_vertices.size(); index < n; ++index) {
		if (m_vertices[index] == from) {
			break;
		}
	}

	if (index == m_vertices.size()) {
		return false;
	}

	m_vertices[index] = to;

	if (IsPosOnBounding(from)) {
		UpdateBounding();
	} else {
		m_bounding.Combine(to);
	}

	return true;
}

void Polyline2DImpl::UpdateBounding()
{
	m_bounding.MakeEmpty();
	for (auto& v : m_vertices) {
		m_bounding.Combine(v);
	}
}

bool Polyline2DImpl::IsPosOnBounding(const sm::vec2& pos) const
{
	return (pos.x == m_bounding.xmin || pos.x == m_bounding.xmax ||
		    pos.y == m_bounding.ymin || pos.y == m_bounding.ymax);
}

}
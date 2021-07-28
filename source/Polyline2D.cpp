#include "geoshape/Polyline2D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polyline2D>("gs_polyline2d")
	.constructor<>()
	.constructor<const std::vector<sm::vec2>&>()
	.property("vertices", &gs::Polyline2D::GetVertices, &gs::Polyline2D::SetVertices)
;

}
#endif // NO_RTTR

namespace gs
{

Polyline2D::Polyline2D(const std::vector<sm::vec2>& vertices)
	: m_impl(vertices, false)
{
	m_bounding = m_impl.GetBounding();
}

std::unique_ptr<Shape2D> Polyline2D::Clone() const
{
	return std::make_unique<Polyline2D>(m_impl.GetVertices());
}

bool Polyline2D::IsContain(const sm::vec2& pos) const
{
	return m_impl.IsContain(pos);
}

bool Polyline2D::IsIntersect(const sm::rect& rect) const
{
	return m_impl.IsIntersect(rect);
}

void Polyline2D::Translate(float dx, float dy)
{
	m_impl.Translate(sm::vec2(dx, dy));
}

void Polyline2D::SetVertices(const std::vector<sm::vec2>& vertices)
{
	m_impl.SetVertices(vertices);
	m_bounding = m_impl.GetBounding();
}

std::vector<sm::vec2> Polyline2D::Resample(const float length) const
{
	std::vector<sm::vec2> pts;
	if (length == 0) {
		return pts;
	}

	auto& vertices = m_impl.GetVertices();
	if (vertices.size() < 2) {
		return pts;
	}

	pts.push_back(vertices[0]);

	int curr_idx = 0;
	float curr_len = length;
	float curr_seg = 0.0f;
	while (curr_idx < vertices.size() - 1)
	{
		float seg_d = sm::dis_pos_to_pos(vertices[curr_idx], vertices[curr_idx + 1]);
		float seg_left = seg_d * (1.0f - curr_seg);
		if (seg_left > curr_len)
		{
			curr_seg += curr_len / seg_d;

			auto dir = (vertices[curr_idx + 1] - vertices[curr_idx]) / seg_d;
			pts.push_back(vertices[curr_idx] + dir * curr_seg * seg_d);

			curr_len = length;
		}
		else
		{
			curr_len -= seg_left;
			curr_seg = 0.0f;

			++curr_idx;
		}
	}

	return pts;
}

}
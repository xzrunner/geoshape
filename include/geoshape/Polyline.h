#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/PolylineImpl.h"

#include <vector>

namespace gs
{

class Polyline : public Shape2D
{
public:
	Polyline() {}
	Polyline(const std::vector<sm::vec2>& vertices);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetVertices() const { return m_impl.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

private:
	PolylineImpl m_impl;

	RTTR_ENABLE(Shape2D)

}; // Polyline

}
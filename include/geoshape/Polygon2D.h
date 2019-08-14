#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/Polyline2DImpl.h"

#include <vector>

namespace gs
{

class Polygon2D : public Shape2D
{
public:
	Polygon2D() {}
	Polygon2D(const std::vector<sm::vec2>& vertices);

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetVertices() const { return m_impl.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

private:
	Polyline2DImpl m_impl;

	RTTR_ENABLE(Shape2D)

}; // Polygon2D

}
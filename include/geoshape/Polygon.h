#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/PolylineImpl.h"

#include <vector>

namespace gs
{

class Polygon : public Shape2D
{
public:
	Polygon() {}
	Polygon(const std::vector<sm::vec2>& vertices);

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetVertices() const { return m_impl.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

private:
	PolylineImpl m_impl;

	RTTR_ENABLE(Shape2D)

}; // Polygon

}
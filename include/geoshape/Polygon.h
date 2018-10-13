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

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Draw(render func) const override {
		m_impl.Draw(func, false);
	}

	auto& GetVertices() const { return m_impl.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

private:
	PolylineImpl m_impl;

	DECLARE_CHILD_CLASS_INFO(Shape)

}; // Polygon

}
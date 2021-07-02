#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/Polyline2DImpl.h"

#include <vector>

namespace gs
{

class Polyline2D : public Shape2D
{
public:
	Polyline2D() {}
	Polyline2D(const std::vector<sm::vec2>& vertices);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Polyline; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetVertices() const { return m_impl.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

    void SetClosed(bool is_closed) { m_impl.SetClosed(is_closed); }
    bool GetClosed() const { return m_impl.GetClosed(); }

private:
	Polyline2DImpl m_impl;

#ifndef NO_RTTR
	RTTR_ENABLE(Shape2D)
#endif // NO_RTTR

}; // Polyline2D

}
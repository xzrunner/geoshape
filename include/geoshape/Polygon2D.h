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
	Polygon2D(const std::vector<sm::vec2>& border);
	Polygon2D(const std::vector<sm::vec2>& border, const std::vector<std::vector<sm::vec2>>& holes);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Polygon; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	auto& GetVertices() const { return m_border.GetVertices(); }
	void SetVertices(const std::vector<sm::vec2>& vertices);

	void AddHole(const std::vector<sm::vec2>& hole);

	const std::vector<sm::vec2>& GetTris() const;

private:
	void BuildTriangles() const;

private:
	Polyline2DImpl m_border;
	std::vector<std::vector<sm::vec2>> m_holes;

	mutable std::vector<sm::vec2> m_tris;

#ifndef NO_RTTR
	RTTR_ENABLE(Shape2D)
#endif // NO_RTTR

}; // Polygon2D

}
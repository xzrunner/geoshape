#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/Polyline2DImpl.h"

#include <vector>

namespace gs
{

class Ellipse : public Shape2D
{
public:
	Ellipse() {}
	Ellipse(const sm::vec2& center, float rx, float ry);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Ellipse; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	const sm::vec2& GetCenter() const { return m_center; }
	void  SetCenter(const sm::vec2& center);

	void GetRadius(float& radius_x, float& radius_y) const;
	void SetRadius(float radius_x, float radius_y);

	auto& GetVertices() const { return m_impl.GetVertices(); }

private:
	std::vector<sm::vec2> TransToPolyline() const;

	void Reset();

private:
	sm::vec2 m_center;
	float    m_radius_x = 1;
	float    m_radius_y = 2;

	Polyline2DImpl m_impl;

}; // Ellipse

}
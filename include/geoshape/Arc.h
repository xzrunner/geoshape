#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/Polyline2DImpl.h"

#include <sm_const.h>

#include <vector>

namespace gs
{

class Arc : public Shape2D
{
public:
	Arc() {}
	Arc(const sm::vec2& center, float radius, float start_angle, float end_angle);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Arc; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	const sm::vec2& GetCenter() const { return m_center; }
	void  SetCenter(const sm::vec2& center);

	float GetRadius() const { return m_radius; }
	void  SetRadius(float radius);

	void GetAngles(float& start_angle, float& end_angle) const;
	void SetAngles(float start_angle, float end_angle);

	auto& GetVertices() const { return m_impl.GetVertices(); }

private:
	std::vector<sm::vec2> TransToPolyline() const;

	void Reset();

private:
	sm::vec2 m_center;
	float    m_radius = 1;

	float m_start_angle = 0;
	float m_end_angle = SM_PI * 0.5f;

	Polyline2DImpl m_impl;

}; // Arc

}
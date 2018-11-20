#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Point2D : public Shape2D
{
public:
	Point2D() {}
	Point2D(const sm::vec2& pos);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetPos() const { return m_pos; }
	void SetPos(const sm::vec2& pos);

private:
	void UpdateBounding();

private:
	sm::vec2 m_pos;

	RTTR_ENABLE(Shape2D)

}; // Point2D

}
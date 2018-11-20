#pragma once

#include "geoshape/Shape.h"

namespace gs
{

class Shape2D : public Shape
{
public:
	Shape2D() {}

	virtual bool IsContain(const sm::vec2& pos) const = 0;
	virtual bool IsIntersect(const sm::rect& rect) const = 0;

protected:
	sm::rect m_bounding;

	RTTR_ENABLE(Shape)

}; // Shape2D

}
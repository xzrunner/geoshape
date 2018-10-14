#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Rect : public Shape2D
{
public:
	Rect() {}
	Rect(const sm::rect& rect);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Draw(render func) const override;

	const sm::rect& GetRect() const { return m_bounding; }
	void SetRect(const sm::rect& r) { m_bounding = r; }

	RTTR_ENABLE(Shape2D)

}; // Rect

}
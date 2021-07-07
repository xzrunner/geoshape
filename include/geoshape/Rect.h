#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Rect : public Shape2D
{
public:
	Rect() {}
	Rect(const sm::rect& rect);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Rect; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	const sm::rect& GetRect() const { return m_bounding; }
	void SetRect(const sm::rect& r) { m_bounding = r; }

#ifndef NO_RTTR
	RTTR_ENABLE(Shape2D)
#endif // NO_RTTR

}; // Rect

}
#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Line2D : public Shape2D
{
public:
	Line2D() {}
	Line2D(const sm::vec2& start, const sm::vec2& end);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Line; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	auto& GetStart() const { return m_start; }
    auto& GetEnd()   const { return m_end; }
	void SetStart(const sm::vec2& start);
    void SetEnd(const sm::vec2& end);

private:
	void UpdateBounding();

private:
	sm::vec2 m_start, m_end;

#ifndef NO_RTTR
	RTTR_ENABLE(Shape2D)
#endif // NO_RTTR

}; // Line2D

}
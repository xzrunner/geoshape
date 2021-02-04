#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Line2D : public Shape2D
{
public:
	Line2D() {}
	Line2D(const sm::vec2& start, const sm::vec2& end);

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	auto& GetStart() const { return m_start; }
    auto& GetEnd()   const { return m_end; }
	void SetStart(const sm::vec2& start);
    void SetEnd(const sm::vec2& end);

private:
	void UpdateBounding();

private:
	sm::vec2 m_start, m_end;

#ifndef RTTR_DISABLE
	RTTR_ENABLE(Shape2D)
#endif // RTTR_DISABLE

}; // Line2D

}
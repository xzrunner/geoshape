#pragma once

#include <SM_Rect.h>

#include <rttr/registration>

namespace gs
{

class Shape2D
{
public:
	Shape2D() {}
    virtual ~Shape2D() {}

    virtual std::unique_ptr<Shape2D> Clone() const = 0;

	virtual bool IsContain(const sm::vec2& pos) const = 0;
	virtual bool IsIntersect(const sm::rect& rect) const = 0;

protected:
	sm::rect m_bounding;

    RTTR_ENABLE()

}; // Shape2D

}
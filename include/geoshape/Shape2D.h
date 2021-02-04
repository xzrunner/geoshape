#pragma once

#include <SM_Rect.h>

#ifndef RTTR_DISABLE
#include <rttr/registration>
#endif // RTTR_DISABLE

#include <memory>

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

#ifndef RTTR_DISABLE
    RTTR_ENABLE()
#endif // RTTR_DISABLE

}; // Shape2D

}
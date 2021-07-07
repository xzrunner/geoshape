#pragma once

#include "geoshape/typedef.h"

#include <SM_Rect.h>

#ifndef NO_RTTR
#include <rttr/registration>
#endif // NO_RTTR

#include <memory>

namespace gs
{

class Shape2D
{
public:
	Shape2D() {}
    virtual ~Shape2D() {}

	virtual ShapeType2D GetType() const = 0;

    virtual std::unique_ptr<Shape2D> Clone() const = 0;

	virtual bool IsContain(const sm::vec2& pos) const = 0;
	virtual bool IsIntersect(const sm::rect& rect) const = 0;

	virtual void Translate(float dx, float dy) = 0;

protected:
	sm::rect m_bounding;

#ifndef NO_RTTR
    RTTR_ENABLE()
#endif // NO_RTTR

}; // Shape2D

}
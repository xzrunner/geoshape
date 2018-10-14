#pragma once

#include <SM_Vector.h>
#include <SM_Rect.h>

#include <rttr/registration>

namespace gs
{

class Shape
{
public:
	virtual ~Shape() {}

	virtual std::unique_ptr<Shape> Clone() const = 0;

	RTTR_ENABLE()

}; // Shape


}
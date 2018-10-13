#pragma once

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <cpputil/ClassInfo.h>

namespace gs
{

class Shape
{
public:
	virtual ~Shape() {}

	virtual std::unique_ptr<Shape> Clone() const = 0;

protected:

	DECLARE_BASE_CLASS_INFO(Shape)

}; // Shape


}
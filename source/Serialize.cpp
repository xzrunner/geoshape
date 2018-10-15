#include "geoshape/Serialize.h"

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<sm::vec2>("sm::vec2")
		.constructor()(rttr::policy::ctor::as_object)
		.property("x", &sm::vec2::x)
		.property("y", &sm::vec2::y)
	;

    rttr::registration::class_<sm::rect>("sm::rect")
		.constructor()(rttr::policy::ctor::as_object)
		.property("xmin", &sm::rect::xmin)
		.property("ymin", &sm::rect::ymin)
		.property("xmax", &sm::rect::xmax)
		.property("ymax", &sm::rect::ymax)
	;
}

namespace gs
{

void Serialize::Init()
{
}

}
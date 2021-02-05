#include "geoshape/Serialize.h"

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <SM_Cube.h>
#ifndef NO_RTTR
#include <rttr/registration>
#endif // NO_RTTR

#ifndef NO_RTTR
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

rttr::registration::class_<sm::vec3>("sm::vec3")
	.constructor()(rttr::policy::ctor::as_object)
	.property("x", &sm::vec3::x)
	.property("y", &sm::vec3::y)
    .property("z", &sm::vec3::z)
;

rttr::registration::class_<sm::cube>("sm::cube")
	.constructor()(rttr::policy::ctor::as_object)
	.property("xmin", &sm::cube::xmin)
	.property("ymin", &sm::cube::ymin)
    .property("zmin", &sm::cube::zmin)
	.property("xmax", &sm::cube::xmax)
	.property("ymax", &sm::cube::ymax)
    .property("zmax", &sm::cube::zmax)
;

}
#endif // NO_RTTR

namespace gs
{

void Serialize::Init()
{
}

}
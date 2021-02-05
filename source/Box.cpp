#include "geoshape/Box.h"

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Box>("gs_box")
	.constructor<>()
	.constructor<const sm::cube&>()
	.property("cube", &gs::Box::GetCube, &gs::Box::SetCube)
;

}
#endif // NO_RTTR

namespace gs
{

Box::Box()
{
    m_bounding = sm::cube(1, 1, 1);
}

Box::Box(const sm::cube& cube)
{
    m_bounding = cube;
}

std::unique_ptr<Shape3D> Box::Clone() const
{
    return std::make_unique<Box>(m_bounding);
}

}
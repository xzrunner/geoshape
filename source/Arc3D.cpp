#include "geoshape/Arc3D.h"
#include "geoshape/config.h"

#include <SM_Calc.h>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Arc3D>("gs_arc3d")
	.constructor<>()
	.constructor<const sm::vec3&, const sm::vec3&>()
	.property("start", &gs::Arc3D::GetStart, &gs::Arc3D::SetStart)
	.property("end", &gs::Arc3D::GetMiddle, &gs::Arc3D::SetMiddle)
    .property("end", &gs::Arc3D::GetEnd, &gs::Arc3D::SetEnd)
;

}
#endif // NO_RTTR

namespace gs
{

Arc3D::Arc3D(const sm::vec3& start, const sm::vec3& mid, const sm::vec3& end)
	: m_start(start)
	, m_mid(mid)
    , m_end(end)
{
	BuildBounding();
}

std::unique_ptr<Shape3D> Arc3D::Clone() const
{
	return std::make_unique<Arc3D>(m_start, m_mid, m_end);
}

void Arc3D::SetStart(const sm::vec3& start)
{
	m_start = start;
	BuildBounding();
}

void Arc3D::SetMiddle(const sm::vec3& mid)
{
	m_mid = mid;
	BuildBounding();
}

void Arc3D::SetEnd(const sm::vec3& end)
{
	m_end = end;
	BuildBounding();
}

void Arc3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    m_bounding.Combine(m_start);
	m_bounding.Combine(m_mid);
    m_bounding.Combine(m_end);
}

}
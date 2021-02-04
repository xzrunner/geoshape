#pragma once

#include <SM_Cube.h>

#ifndef RTTR_DISABLE
#include <rttr/registration>
#endif // RTTR_DISABLE

#include <memory>

namespace gs
{

class Shape3D
{
public:
    Shape3D() {}
    virtual ~Shape3D() {}

    virtual std::unique_ptr<Shape3D> Clone() const = 0;

//    virtual bool IsContain(const sm::vec3& pos) const = 0;

    auto& GetBounding() const { return m_bounding; }

protected:
    sm::cube m_bounding;

#ifndef RTTR_DISABLE
    RTTR_ENABLE()
#endif // RTTR_DISABLE

}; // Shape3D

}
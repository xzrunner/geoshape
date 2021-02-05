#pragma once

#include "geoshape/Shape3D.h"

#include <vector>

namespace gs
{

class Polyline3D : public Shape3D
{
public:
    Polyline3D();
    Polyline3D(const std::vector<sm::vec3>& vertices,
        bool is_closed = false);

    virtual std::unique_ptr<Shape3D> Clone() const override;

    auto& GetVertices() const { return m_vertices; }
    void SetVertices(const std::vector<sm::vec3>& vertices);

    bool GetClosed() const { return m_is_closed; }
    void SetClosed(bool closed) { m_is_closed = closed; }

private:
    void BuildBounding();

private:
    std::vector<sm::vec3> m_vertices;
    bool m_is_closed = false;

#ifndef NO_RTTR
    RTTR_ENABLE(Shape3D)
#endif // NO_RTTR

}; // Polyline3D

}
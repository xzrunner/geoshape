#pragma once

#include "geoshape/Shape3D.h"

#include <vector>

namespace gs
{

class Polygon3D : public Shape3D
{
public:
    Polygon3D();
    Polygon3D(const std::vector<sm::vec3>& vertices);

    virtual std::unique_ptr<Shape3D> Clone() const override;

    auto& GetVertices() const { return m_vertices; }
    void SetVertices(const std::vector<sm::vec3>& vertices);

private:
    void BuildBounding();

private:
    std::vector<sm::vec3> m_vertices;

#ifndef RTTR_DISABLE
    RTTR_ENABLE(Shape3D)
#endif // RTTR_DISABLE

}; // Polygon3D

}
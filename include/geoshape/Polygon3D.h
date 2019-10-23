#pragma once

#include "geoshape/Shape3D.h"

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

    RTTR_ENABLE(Shape3D)

}; // Polygon3D

}
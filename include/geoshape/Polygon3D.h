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

    const std::vector<unsigned short>& GetTris() const;

private:
    void BuildBounding();

    void BuildTriangles() const;

private:
    std::vector<sm::vec3> m_vertices;

    mutable std::vector<unsigned short> m_tris;

#ifndef NO_RTTR
    RTTR_ENABLE(Shape3D)
#endif // NO_RTTR

}; // Polygon3D

}
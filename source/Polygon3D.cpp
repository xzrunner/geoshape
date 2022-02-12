#include "geoshape/Polygon3D.h"

#include <SM_Calc.h>
#include <SM_Triangulation.h>

#include <map>

#ifndef NO_RTTR
RTTR_REGISTRATION
{

rttr::registration::class_<gs::Polygon3D>("gs_polygon3d")
	.constructor<>()
	.constructor<const std::vector<sm::vec3>&>()
	.property("vertices", &gs::Polygon3D::GetVertices, &gs::Polygon3D::SetVertices)
;

}
#endif // NO_RTTR

namespace gs
{

Polygon3D::Polygon3D()
{
    BuildBounding();
}

Polygon3D::Polygon3D(const std::vector<sm::vec3>& vertices)
    : m_vertices(vertices)
{
    BuildBounding();
}

std::unique_ptr<Shape3D> Polygon3D::Clone() const
{
    return std::make_unique<Polygon3D>(m_vertices);
}

void Polygon3D::SetVertices(const std::vector<sm::vec3>& vertices)
{
    m_vertices = vertices;

    BuildBounding();
}

const std::vector<unsigned short>& Polygon3D::GetTris() const
{ 
	if (m_tris.empty()) {
		BuildTriangles();
	}
	return m_tris; 
}

void Polygon3D::BuildBounding()
{
    m_bounding.MakeEmpty();
    for (auto& v : m_vertices) {
        m_bounding.Combine(v);
    }
}

void Polygon3D::BuildTriangles() const
{
    m_tris.clear();

    auto norm = sm::calc_face_normal(m_vertices);
    auto rot = sm::mat4(sm::Quaternion::CreateFromVectors(norm, sm::vec3(0, 1, 0)));

    std::map<sm::vec2, size_t> pos2idx;
    auto trans_loop3to2 = [&](const std::vector<sm::vec3>& verts) -> std::vector<sm::vec2>
    {
        std::vector<sm::vec2> loop2;
        loop2.reserve(verts.size());
        for (size_t i = 0; i < verts.size(); ++i)
        {
            auto& pos3 = verts[i];
            auto p3_rot = rot * pos3;
            sm::vec2 pos2(p3_rot.x, p3_rot.z);
            auto status = pos2idx.insert({ pos2, i });
//            assert(status.second);

            loop2.push_back(pos2);
        }
        return loop2;
    };

    auto border2 = trans_loop3to2(m_vertices);

    std::vector<sm::vec2> tris;
    try {
        sm::triangulate_normal(border2, tris);
    } catch (...) {
        return;
    }
    assert(tris.size() % 3 == 0);
    m_tris.reserve(tris.size());
    for (size_t i = 0, n = tris.size(); i < n; )
    {
        std::vector<sm::vec2*> tri(3);
        for (size_t j = 0; j < 3; ++j) {
            tri[j] = &tris[i++];
        }
        if (sm::is_turn_left(*tri[0], *tri[1], *tri[2])) {
            std::reverse(tri.begin(), tri.end());
        }
        for (size_t j = 0; j < 3; ++j)
        {
            auto itr = pos2idx.find(*tri[j]);
            if (itr == pos2idx.end())
            {
                float min_dist = FLT_MAX;
                int min_idx = -1;
                for (auto itr = pos2idx.begin(); itr != pos2idx.end(); ++itr) 
                {
                    float d = sm::dis_pos_to_pos(*tri[j], itr->first);
                    if (d < min_dist) {
                        min_dist = d;
                        min_idx = itr->second;
                    }
                }
                assert(min_idx >= 0);
                m_tris.push_back(static_cast<size_t>(min_idx));
            }
            else
            {
                m_tris.push_back(itr->second);
            }
        }
    }
}

}
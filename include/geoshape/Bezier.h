#pragma once

#include "geoshape/Shape2D.h"
#include "geoshape/PolylineImpl.h"

#include <primitive/Bezier.h>

#include <vector>

namespace gs
{

class Bezier : public Shape2D
{
public:
	Bezier() {}
	Bezier(const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>& ctrl_nodes);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	void SetCtrlPos(const std::array<sm::vec2, prim::Bezier::CTRL_NODE_COUNT>& ctrl_nodes);
	auto& GetCtrlPos() const { return m_bezier.GetCtrlNodes(); }

	auto& GetVertices() const { return m_impl.GetVertices(); }

private:
	PolylineImpl m_impl;

	prim::Bezier m_bezier;

	RTTR_ENABLE(Shape2D)

}; // Bezier

}
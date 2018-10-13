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
	Bezier(const sm::vec2& v0, const sm::vec2& v1,
		   const sm::vec2& v2, const sm::vec2& v3);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Draw(render func) const override {
		m_impl.Draw(func, false);
	}

	void SetCtrlPos(const sm::vec2& v0, const sm::vec2& v1,
		const sm::vec2& v2, const sm::vec2& v3);

	auto& GetVertices() const { return m_impl.GetVertices(); }

private:
	PolylineImpl m_impl;

	prim::Bezier m_bezier;

	DECLARE_CHILD_CLASS_INFO(Shape)

}; // Bezier

}
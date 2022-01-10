#pragma once

#include "geoshape/Shape2D.h"

#include <vector>

namespace gs
{

class Triangles : public Shape2D
{
public:
	Triangles() {}
	Triangles(const std::vector<sm::vec2>& border);

	virtual ShapeType2D GetType() const override { return ShapeType2D::Triangles; }

	virtual std::unique_ptr<Shape2D> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Translate(float dx, float dy) override;

	auto& GetBorder() const { return m_border; }
	void SetBorder(const std::vector<sm::vec2>& border);

	auto& GetTris() const { return m_tris; }

private:
	void Update();

	void UpdateBounding();
	void BuildTriangles();

private:
	std::vector<sm::vec2> m_border;
	std::vector<sm::vec2> m_tris;

}; // Triangles

}
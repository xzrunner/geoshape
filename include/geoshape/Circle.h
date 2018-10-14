#pragma once

#include "geoshape/Shape2D.h"

namespace gs
{

class Circle : public Shape2D
{
public:
	Circle() {}
	Circle(const sm::vec2& center, float radius);

	virtual std::unique_ptr<Shape> Clone() const override;

	virtual bool IsContain(const sm::vec2& pos) const override;
	virtual bool IsIntersect(const sm::rect& rect) const override;

	virtual void Draw(render func) const override {
		// todo
	}

	const sm::vec2& GetCenter() const { return m_center; }
	void  SetCenter(const sm::vec2& center);

	float GetRadius() const { return m_radius; }
	void  SetRadius(float radius);

private:
	void UpdateBounding();

private:
	sm::vec2 m_center;
	float    m_radius;

	RTTR_ENABLE(Shape2D)

}; // Circle

}
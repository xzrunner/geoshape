#pragma once

#include "geoshape/Shape3D.h"

namespace gs
{

class Line3D : public Shape3D
{
public:
	Line3D() {}
	Line3D(const sm::vec3& start, const sm::vec3& end);

	virtual std::unique_ptr<Shape3D> Clone() const override;

	auto& GetStart() const { return m_start; }
    auto& GetEnd()   const { return m_end; }
	void SetStart(const sm::vec3& start);
    void SetEnd(const sm::vec3& end);

private:
	void BuildBounding();

private:
	sm::vec3 m_start, m_end;

#ifndef NO_RTTR
	RTTR_ENABLE(Shape3D)
#endif // NO_RTTR

}; // Line3D

}
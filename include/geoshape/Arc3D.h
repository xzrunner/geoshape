#pragma once

#include "geoshape/Shape3D.h"

namespace gs
{

class Arc3D : public Shape3D
{
public:
	Arc3D() {}
	Arc3D(const sm::vec3& start, const sm::vec3& mid, const sm::vec3& end);

	virtual std::unique_ptr<Shape3D> Clone() const override;

	auto& GetStart() const { return m_start; }
	auto& GetMiddle() const { return m_mid; }
    auto& GetEnd()   const { return m_end; }
	void SetStart(const sm::vec3& start);
	void SetMiddle(const sm::vec3& mid);
    void SetEnd(const sm::vec3& end);

private:
	void BuildBounding();

private:
	sm::vec3 m_start, m_mid, m_end;

#ifndef NO_RTTR
	RTTR_ENABLE(Shape3D)
#endif // NO_RTTR

}; // Arc3D

}
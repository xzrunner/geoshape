#pragma once

#include <SM_Vector.h>
#include <SM_Rect.h>

#include <vector>
#include <functional>

namespace gs
{

class Polyline2DImpl
{
public:
	Polyline2DImpl() {}
	Polyline2DImpl(const std::vector<sm::vec2>& vertices,
		bool is_closed = false);

	bool IsContain(const sm::vec2& pos) const;
	bool IsIntersect(const sm::rect& rect) const;

	auto& GetVertices() const { return m_vertices; }
	void SetVertices(const std::vector<sm::vec2>& vertices);

	// for editor
	bool AddVertex(int index, const sm::vec2& pos);
	bool RemoveVertex(const sm::vec2& pos);
	bool ChangeVertex(const sm::vec2& from, const sm::vec2& to);

	auto& GetBounding() const { return m_bounding; }

    void SetClosed(bool is_closed) { m_is_closed = is_closed; }
    bool GetClosed() const { return m_is_closed; }

	void Translate(const sm::vec2& offset);

private:
	void UpdateBounding();

	bool IsPosOnBounding(const sm::vec2& pos) const;

private:
	std::vector<sm::vec2> m_vertices;
	bool m_is_closed = false;

	sm::rect m_bounding;

}; // Polyline2DImpl

}
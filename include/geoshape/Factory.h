#pragma once

#include <cu/cu_macro.h>
#include <cpputil/ClassInfo.h>

#include <map>

namespace gs
{

class Shape;

class Factory
{
public:
	void Register(cpputil::ClassInfo<Shape>* ci);
	std::unique_ptr<Shape> Create(const std::string& class_name);

private:
	std::map<std::string, cpputil::ClassInfo<Shape>*>  m_shape_map;

	CU_SINGLETON_DECLARATION(Factory)

}; // Factory

}
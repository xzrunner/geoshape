#include "geoshape/Factory.h"
#include "geoshape/Shape.h"

namespace gs
{

CU_SINGLETON_DEFINITION(Factory);

Factory::Factory()
{
}

void Factory::Register(cpputil::ClassInfo<Shape>* ci)
{
	auto& name = ci->GetClassName();
	if (m_shape_map.find(name) == m_shape_map.end()) {
		m_shape_map.insert({ name, ci });
	}
}

std::unique_ptr<Shape> Factory::Create(const std::string& class_name)
{
	auto itr = m_shape_map.find(class_name);
	if (itr == m_shape_map.end()) {
		return nullptr;
	}

	return itr->second->GetCtor()();
}

}
#pragma once
#include <PropertyDescription.hpp>
#include <string>
#include <vector>

namespace easygen
{
	struct DataModelDescription
	{
	public:
		DataModelDescription() = default;
		virtual ~DataModelDescription() = default;

		std::string m_namespace_last = "datamodel";
		std::string m_class_name;
		std::string m_object_type;
		std::vector<PropertyDescription> m_property_descriptions_;
	};
}

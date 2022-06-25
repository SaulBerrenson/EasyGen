#pragma once
#include <string>


namespace easygen
{
	class PropertyDescription
	{
	public:
		std::string m_name;
		std::string m_type;
		std::string m_description;
		bool is_last = false;
	};
}
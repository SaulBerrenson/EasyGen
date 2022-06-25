#pragma once
#include "Forwards.hpp"


namespace easygen
{
	/*!
	 * @brief Get C++ base types conversion table
	 * @return cpp base types conversion table
	*/
	inline DataTypeMapping CppBaseTypes()
	{
		return{
			{"string", std::make_pair("std::string","\"\"")},
			{"int64",std::make_pair("int64_t","0")},
			{"int32",std::make_pair("int32_t","0")},
			{"bool",std::make_pair("bool","false")},
			{"byte",std::make_pair("uint8_t","0x0")},
			{"uint64", std::make_pair("uint64_t","0")},
			{"uint32", std::make_pair("uint32_t","0")},
		};
	}
}

#pragma once
#include <string>
#include <vector>

namespace easygen
{
	/*fwd decl*/
	struct DataModelDescription;

	using ListDataModels = std::vector<DataModelDescription>;
	using ErrorMsg = std::string;


	using DefaultValue = std::string;
	using PlatformType = std::string;
	using DataTypeMapping = std::map<std::string, std::tuple<PlatformType, DefaultValue>>;
}

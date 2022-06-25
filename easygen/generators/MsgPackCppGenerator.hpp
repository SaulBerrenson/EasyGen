#pragma once
#include "AbstractGenerator.hpp"
#include "DataTypeBasic.hpp"

namespace easygen
{
	class MsgPackCppGenerator : public easygen::AbstractGenerator
	{
	public:
		MsgPackCppGenerator(const std::vector<easygen::DataModelDescription>& models)
			: AbstractGenerator(easygen::CppBaseTypes(), models)
		{
		}

		std::vector<std::string> GenerateData(const boost::filesystem::path& output_dir) override;
	};
}

#pragma once
#include "AbstractGenerator.hpp"
#include "DataTypeBasic.hpp"

namespace easygen
{
	class MsgPackCppGenerator : public easygen::AbstractGenerator
	{
	public:
		/*!
		 * @brief ctor (only input models)
		 * @param models - data models from yaml
		*/
		MsgPackCppGenerator(const std::vector<easygen::DataModelDescription>& models);

		/*! @copydoc AbstractGenerator::GenerateData(const boost::filesystem::path& output_dir) */
		std::vector<std::string> GenerateData(const boost::filesystem::path& output_dir) override;
	};
}

#pragma once
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <mstch/mstch.hpp>

#include "DataModelDescription.hpp"
#include "Forwards.hpp"


namespace easygen
{
	/*!
	 * @brief Abstract class for generation
	*/
	class AbstractGenerator
	{
	public:
		AbstractGenerator(const DataTypeMapping& data_conversion, const std::vector<DataModelDescription>& models);

		virtual ~AbstractGenerator() = default;
		/*!
		 * @brief Generate project from input models to output dirs
		 * @param output_dir - path to directory where generate result files
		 * @return same txt-files, but at string list (for testing and validation)
		*/
		virtual std::vector<std::string> GenerateData(const boost::filesystem::path& output_dir) = 0;

	protected:
		/*!
		 * @brief convert yaml type to specified platform and language
		 * @param data_type - yaml type
		 * @return specified platform or language type
		*/
		PlatformType ConvertType(const std::string& data_type) const;
		/*!
		 * @brief Get default value for yaml type
		 * @param data_type yaml type
		 * @return specified platform or language default value
		 * @details example int64 - int64_t (cpp) and default value -> 0
		*/
		DefaultValue DefaultValueType(const std::string& data_type) const;
		/*!
		 * @brief help function for converting datamodel to mustache context
		 * @param data_model data model from yaml config
		 * @return mustache context for generation data from tempaltes
		*/
		mstch::map ConvertModelToContext(const DataModelDescription& data_model) const;

		/*!
		 * @brief list mustache context
		*/
		std::vector<mstch::map> m_context_models;
		/*!
		 * @brief - dictionary yaml-type -> [conversion type, default value]
		*/
		const DataTypeMapping& m_type_conversion;
	};
}

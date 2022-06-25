#pragma once
#include <boost/algorithm/string/case_conv.hpp>
#include <mstch/mstch.hpp>

#include "DataModelDescription.hpp"
#include "Forwards.hpp"


namespace easygen
{
	class AbstractGenerator
	{
	public:
		AbstractGenerator(const DataTypeMapping& data_conversion, const std::vector<DataModelDescription>& models);

		virtual ~AbstractGenerator() = default;

		virtual std::vector<std::string> GenerateData(const std::string& output_dir) = 0;

	protected:
		PlatformType ConvertType(const std::string& data_type) const;
		DefaultValue DefaultValueType(const std::string& data_type) const;

		mstch::map ConvertModelToContext(const DataModelDescription& data_model) const;


		std::vector<mstch::map> m_context_models;
		const DataTypeMapping& m_type_conversion;
	};
}

#include "AbstractGenerator.hpp"
#include "Labels.hpp"


namespace easygen
{
	AbstractGenerator::AbstractGenerator(const DataTypeMapping& data_conversion,
		const std::vector<DataModelDescription>& models) : m_type_conversion(data_conversion)
	{
		for (const auto& model : models)
		{
			m_context_models.push_back(AbstractGenerator::ConvertModelToContext(model));
		}
	}

	std::string AbstractGenerator::ConvertType(const std::string& data_type) const
	{
		return std::get<0>(m_type_conversion.at(data_type));
	}

	DefaultValue AbstractGenerator::DefaultValueType(const std::string& data_type) const
	{
		return std::get<1>(m_type_conversion.at(data_type));
	}

	mstch::map AbstractGenerator::ConvertModelToContext(const DataModelDescription& data_model) const
	{
		mstch::map context{};

		const auto& class_name = data_model.m_class_name;

		context[easygen::labels::class_name] = class_name;
		context[easygen::labels::class_name_lower] = boost::algorithm::to_lower_copy(class_name);
		context[easygen::labels::class_name_upper] = boost::algorithm::to_upper_copy(class_name);
		context[easygen::labels::namespace_name] = data_model.m_namespace_last;

		mstch::array property_array{};

		for (const auto& default_model : data_model.m_property_descriptions_)
		{
			auto data_type = default_model.m_type;

			property_array.push_back(mstch::map{
				{easygen::labels::property_type,ConvertType(data_type)},
				{easygen::labels::property_name, default_model.m_name},
				{easygen::labels::property_default_value, DefaultValueType(data_type)},
				{easygen::labels::property_description, mstch::map{{"value",default_model.m_description}}},
				{easygen::labels::property_last, std::string{!default_model.is_last ? "" : "true"}}
				});
		}

		context[easygen::labels::property_list] = std::move(property_array);

		return context;
	}
}

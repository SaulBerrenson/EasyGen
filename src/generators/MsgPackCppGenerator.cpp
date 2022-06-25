#include "MsgPackCppGenerator.hpp"

#include <mutex>

#include "Helper.hpp"
#include "Labels.hpp"

namespace easygen
{
	std::vector<std::string> MsgPackCppGenerator::GenerateData(const std::string& output_dir)
	{
		boost::filesystem::path path_to_templates = easygen::io::get_path_to_template_dir() / "DtoMsgPack";


		std::vector<std::string> out;

		std::string hpp_template;
		std::string cpp_template;
		std::string base_template;
		std::string cmake_template;

		{
			auto hpp_template_path = path_to_templates / "ModelHpp.template";
			auto cpp_template_path = path_to_templates / "ModelCpp.template";
			auto base_serializer_template_path = path_to_templates / "IBaseSerializerHpp.template";
			auto cmake_template_path = path_to_templates / "CMakeLists.template";

			boost::filesystem::load_string_file(hpp_template_path, hpp_template);
			boost::filesystem::load_string_file(cpp_template_path, cpp_template);
			boost::filesystem::load_string_file(base_serializer_template_path, base_template);
			boost::filesystem::load_string_file(cmake_template_path, cmake_template);
		}

		auto out_dir = boost::filesystem::path(output_dir);
		auto include_dir = out_dir / "include";
		auto src_dir = out_dir / "src";

		if (!boost::filesystem::exists(boost::filesystem::path(output_dir)))
			boost::filesystem::create_directories(boost::filesystem::path(output_dir));

		if (!boost::filesystem::exists(include_dir))
			boost::filesystem::create_directories(include_dir);

		if (!boost::filesystem::exists(src_dir))
			boost::filesystem::create_directories(src_dir);

		std::once_flag once_serializer_create;

		for (const auto& context_model : m_context_models)
		{
			/*create hpp*/
			const auto data_hpp = mstch::render(hpp_template, context_model);
			/*create cpp*/
			const auto data_cpp = mstch::render(cpp_template, context_model);


			auto class_name = boost::get<std::string>(context_model.at(easygen::labels::class_name));

			{
				auto hpp_file = class_name;
				hpp_file.append(".hpp");
				boost::filesystem::save_string_file(include_dir / hpp_file, data_hpp);
			}

			{
				auto cpp_file = class_name;
				cpp_file.append(".cpp");
				boost::filesystem::save_string_file(src_dir / cpp_file, data_cpp);
			}

			std::call_once(once_serializer_create,
			               [&]()
			               {
				               const auto base_hpp = mstch::render(base_template, context_model);
				               boost::filesystem::save_string_file(include_dir / "IBinarySerializer.hpp", base_hpp);
				               out.push_back(base_hpp);
			               });


			out.push_back(data_hpp);
			out.push_back(data_cpp);
		}

		boost::filesystem::save_string_file(out_dir / "CMakeLists.txt", cmake_template);

		return out;
	}
}

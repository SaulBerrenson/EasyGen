#pragma once
#include "YamlDeserializationHelper.hpp"
#include <stdexcept>
#include <boost/filesystem.hpp>

namespace easygen
{
	namespace io
	{		
       inline bool load_model_from_file(const std::string& path_to_config,
                                        std::vector<DataModelDescription>& models_out,
										std::string& err_msg_out)
       {
		   boost::filesystem::path path_config(path_to_config);

		   if (!boost::filesystem::exists(path_to_config)) { err_msg_out = "file is not exist"; return false; };

		   YAML::Node config = YAML::LoadFile(path_to_config);

		   auto models = config["models"];

		   for (const auto& it : models)
		   {
			   auto data_model = it.second.as<DataModelDescription>();

			   data_model.m_class_name = it.first.Scalar();
			   models_out.push_back(data_model);
		   }

		   return true;
       }
	}
}


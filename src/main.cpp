#include <chrono>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <mstch/mstch.hpp>

#include "ConfigLoader.hpp"
#include "Factory.hpp"
#include "Helper.hpp"

int main(int argc, char* argv[])
{
	namespace po = boost::program_options;

	std::string selected_generator;
	boost::filesystem::path config_file = easygen::io::get_current_path() / "test.yaml";

	constexpr const char* lbl_list_generators = "list";
	constexpr const char* lbl_generator = "generator";
	constexpr const char* lbl_config = "config";


	po::options_description desc("list options");
	desc.add_options()
		(lbl_list_generators, "get available generators")
		(lbl_generator, po::value<std::string>(&selected_generator), "config for generation")
		(lbl_config, po::value<boost::filesystem::path>(&config_file), "set config for generations");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count(lbl_list_generators))
	{
		std::cout << "========================================" << std::endl;
		std::cout << "----------Available generators----------" << std::endl;
		for (const auto& generator_name : easygen::get_list_generators())
		{
			std::cout << generator_name << std::endl;
		}
		std::cout << "========================================" << std::endl;
		return 0;
	}

	if (!vm.count(lbl_generator) && !vm.count(lbl_config))
	{
		desc.print(std::cout); /*print info about keys*/
		return 0;
	}

	std::cout << "use config: " << config_file.string() << std::endl;

	if (!boost::filesystem::exists(config_file))
	{
		std::cout << "config file isn't exist" << std::endl;
		return -100;
	}

	if (easygen::Generators.find(selected_generator) == easygen::Generators.end())
	{
		std::cout << "generator isn't exist" << std::endl;
		return -200;
	}

	easygen::ListDataModels models;
	easygen::ErrorMsg error;

	if (!easygen::io::load_model_from_file(config_file, models, error))
	{
		std::cout << error << std::endl;
		return -300;
	}

	auto generator = easygen::Generators.at(selected_generator)(models); /*create generator*/

	const auto temp_folder_name = std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	const auto output_path = easygen::io::get_path_to_temp_dir() / temp_folder_name;

	auto result = generator->GenerateData(output_path.string());

	std::cout << "result at -> " << output_path.string() << std::endl;
}

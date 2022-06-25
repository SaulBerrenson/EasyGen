#pragma once
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <boost/filesystem/string_file.hpp>

namespace easygen
{
	namespace io
	{
		inline boost::filesystem::path get_current_path()
		{
			return boost::dll::program_location().parent_path();
		}

		inline boost::filesystem::path get_path_to_temp_dir()
		{
			return get_current_path() / "tmp";
		}

		inline boost::filesystem::path get_path_to_template_dir()
		{
			return get_current_path() / "templates";
		}

	}
}

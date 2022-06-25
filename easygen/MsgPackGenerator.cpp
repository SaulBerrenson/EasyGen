#include "MsgPackGenerator.hpp"

#include <iostream>
#include "Helper.hpp"

std::vector<std::string> MsgPackGenerator::GenerateData(const std::string& output_dir)
{
    std::vector<std::string> out;

    auto view_path = "D:\\SystemFile\\Desktop\\test_server\\project\\build\\bin\\Debug\\CppNlohmanJson\\ModelHpp.mustache";
    auto view_path_2 = "D:\\SystemFile\\Desktop\\test_server\\project\\build\\bin\\Debug\\CppNlohmanJson\\ModelCpp.mustache";

    std::string view;
	boost::filesystem::load_string_file(view_path, view);

    std::string view2;
    boost::filesystem::load_string_file(view_path_2, view2);

    for (const auto& context_model : m_context_models)
    {
        auto data_hpp = mstch::render(view, context_model);
        auto data_cpp = mstch::render(view2, context_model);

        out.push_back(data_hpp);
        out.push_back(data_cpp);

        std::cout << data_hpp << std::endl;
    }

    return out;
}

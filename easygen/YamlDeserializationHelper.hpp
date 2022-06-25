#pragma once
#include <yaml-cpp/yaml.h>
#include "DataModelDescription.hpp"
#include "PropertyDescription.hpp"

namespace YAML {
    template<>
    struct convert<easygen::PropertyDescription> {

        static bool decode(const Node& node, easygen::PropertyDescription& rhs) {

            rhs.m_type = node["type"].as<std::string>();

            if (node["description"].IsDefined())
                rhs.m_description = node["description"].as<std::string>();

            return true;
        }
    };

    template<>
    struct convert<easygen::DataModelDescription> {

        static bool decode(const Node& node, easygen::DataModelDescription& rhs) {

            rhs.m_object_type = node["type"].as<std::string>();

            auto props = node["properties"];

            for (const auto& prop_value : props)
            {
                auto property_data = prop_value.second.as<easygen::PropertyDescription>();
                property_data.m_name = prop_value.first.Scalar();

                rhs.m_property_descriptions_.push_back(property_data);
            }

            if (!rhs.m_property_descriptions_.empty())
                (rhs.m_property_descriptions_.end() - 1)->is_last = true;

            return true;
        }
    };

}

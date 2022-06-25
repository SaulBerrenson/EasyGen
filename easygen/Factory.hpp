#pragma once
#include <map>
#include <string>
#include <vector>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "MsgPackCppGenerator.hpp"

#include <Forwards.hpp>


namespace easygen
{
	using FactoryFn_t =  std::function<std::shared_ptr<AbstractGenerator>(const std::vector<DataModelDescription>& models)>;

	template<class TGenerator>
	FactoryFn_t FactoryMethod()
	{
		return FactoryFn_t([](const std::vector<DataModelDescription>& models) { return std::make_shared<TGenerator>(models); });
	}

	static std::map<std::string, FactoryFn_t> Generators
	{
		{"msgpack_cpp", FactoryMethod<MsgPackCppGenerator>()}

	};

	inline std::vector<std::string> get_list_generators()
	{	
		std::vector<std::string> list_outs;
		boost::copy(Generators | boost::adaptors::map_keys, std::back_inserter(list_outs));
		return list_outs;
	}
}

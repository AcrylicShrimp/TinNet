
/*
	2019.03.20
	Created by AcrylicShrimp.
*/

#include "NodeTypeManager.h"

namespace TinNet::Node
{
	NodeTypeManager::NodeTypeManager()
	{
		auto sTypeName{Node::typeName()};

		this->sNodeTypeMap.emplace(std::piecewise_construct, std::forward_as_tuple(std::string{sTypeName}), std::forward_as_tuple(nullptr, sTypeName));
	}
}
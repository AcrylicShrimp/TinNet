
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_VARIABLENODE_H

#define _CLASS_TINNET_GRAPHNODE_VARIABLENODE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../CacheContainer.h"
#include "../Graph.h"
#include "../Initializable.h"
#include "FullNode.h"

#include <cstddef>
#include <string>
#include <vector>

namespace TinNet::GraphNode
{
	class TINNET_DLL VariableNode : public FullNode, public Initializable
	{
	protected:
		std::vector<std::size_t> sVariableSizeList;
		std::vector<CachePtr> sVariableList;
		std::vector<CachePtr> sVariableGradientList;
		
	public:
		VariableNode(Graph *pGraph, const std::string &sName);
		VariableNode(const VariableNode &sSrc) = delete;
		~VariableNode();
		
	public:
		VariableNode &operator=(const VariableNode &sSrc) = delete;
		
	public:
		virtual void notifyShapeUpdated() override;
		virtual void notifyBackwardEnabled() override;
		virtual void notifyBackwardDisabled() override;

	protected:
		inline void registerVariable(std::size_t nSize);
	};

	inline void VariableNode::registerVariable(std::size_t nSize)
	{
		return this->sVariableSizeList.emplace_back(nSize);
	}
}

#endif
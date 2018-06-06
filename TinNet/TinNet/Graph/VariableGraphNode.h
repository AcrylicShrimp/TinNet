
/*
	2018.06.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_VARIABLEGRAPHNODE_H

#define _CLASS_TINNET_GRAPH_VARIABLEGRAPHNODE_H

#include "../TinNetDLL.h"

#include "../Shape.h"
#include "CacheContainer.h"
#include "Graph.h"
#include "FullCachedGraphNode.h"

#include <cstddef>
#include <string>
#include <vector>

//DELETEME : For testing purpose.
#include <cmath>
#include <random>

namespace TinNet::Graph
{
	class TINNET_DLL VariableGraphNode : public FullCachedGraphNode
	{
	protected:
		std::vector<std::size_t> sVariableSizeList;
		std::vector<CacheContainer::CacheInfo *> sVariableList;
		std::vector<CacheContainer::CacheInfo *> sVariableBackwardList;
		
	public:
		VariableGraphNode(const std::string &sName, Graph *pGraph);
		VariableGraphNode(const VariableGraphNode &sSrc) = delete;
		~VariableGraphNode();
		
	public:
		VariableGraphNode &operator=(const VariableGraphNode &sSrc) = delete;
		
	public:
		virtual std::size_t fanIn() const = 0;
		virtual std::size_t fanOut() const = 0;
		virtual void backwardVariablePass() = 0;
		virtual void enableBackward() override;
		virtual void disableBackward() override;
		virtual void initGraph() override;
		void initialize();
		void applyGradient(float nFactor);
		
	protected:
		inline void variable(std::size_t nSize);
	};

	inline void VariableGraphNode::variable(std::size_t nSize)
	{
		this->sVariableSizeList.emplace_back(nSize);
	}
}

#endif
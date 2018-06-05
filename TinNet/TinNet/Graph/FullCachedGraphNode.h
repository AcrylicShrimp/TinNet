
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_FULLCACHEDGRAPHNODE_H

#define _CLASS_TINNET_GRAPH_FULLCACHEDGRAPHNODE_H

#include "../TinNetDLL.h"

#include "BackwardCachedGraphNode.h"
#include "../Cache.h"
#include "CacheContainer.h"
#include "Graph.h"

#include <string>

namespace TinNet::Graph
{
	class TINNET_DLL FullCachedGraphNode : public BackwardCachedGraphNode
	{
	protected:
		CacheContainer::CacheInfo *pForward;

	public:
		FullCachedGraphNode(const std::string &sName, Graph *pGraph);
		FullCachedGraphNode(const FullCachedGraphNode &sSrc) = delete;
		~FullCachedGraphNode();

	public:
		FullCachedGraphNode &operator=(const FullCachedGraphNode &sSrc) = delete;

	public:
		virtual void initGraph() override;
		virtual const Cache &forward() override;
	};
}

#endif
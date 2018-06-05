
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_BACKWARDCACHEDGRAPHNODE_H

#define _CLASS_TINNET_GRAPH_BACKWARDCACHEDGRAPHNODE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "CacheContainer.h"
#include "Graph.h"
#include "GraphNode.h"

#include <string>

namespace TinNet::Graph
{
	class TINNET_DLL BackwardCachedGraphNode : public GraphNode
	{
	protected:
		CacheContainer::CacheInfo *pBackward;
		CacheContainer::CacheInfo *pBackwardTemp;
		
	public:
		BackwardCachedGraphNode(const std::string &sName, Graph *pGraph);
		BackwardCachedGraphNode(const BackwardCachedGraphNode &sSrc) = delete;
		~BackwardCachedGraphNode() = default;
		
	public:
		BackwardCachedGraphNode &operator=(const BackwardCachedGraphNode &sSrc) = delete;
		
	public:
		virtual void enableBackward() override;
		virtual void disableBackward() override;
		virtual const Cache &backward() override;
	};
}

#endif
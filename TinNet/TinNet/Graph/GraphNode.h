
/*
	2018.05.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_GRAPHNODE_H

#define _CLASS_TINNET_GRAPH_GRAPHNODE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Shape.h"
#include "CacheContainer.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace TinNet::Graph
{
	class TINNET_DLL GraphNode
	{
	protected:
		std::string sName;
		class Graph *pGraph;
		std::vector<GraphNode *> sForwardList;
		std::vector<GraphNode *> sBackwardList;
		
	public:
		GraphNode(const std::string &sName, Graph *pGraph);
		GraphNode(const GraphNode &sSrc) = delete;
		virtual ~GraphNode() = default;
		
	public:
		GraphNode &operator=(const GraphNode &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const = 0;
		virtual std::size_t maxBackwardNodeCount() const;
		virtual void initNode() = 0;
		virtual void initGraph() = 0;
		virtual void enableBackward() = 0;
		virtual void disableBackward() = 0;
		virtual const Cache &forward() = 0;
		virtual const Cache &backward() = 0;
		inline const std::string &name() const;
		inline std::size_t forwardNodeCount() const;
		inline std::size_t backwardNodeCount() const;
		inline bool isLeafForward() const;
		inline bool isLeafBackward() const;
		static void link(GraphNode *pBackward, GraphNode *pForward);
		static void unlink(GraphNode *pBackward, GraphNode *pForward);

	protected:
		virtual void forwardPass(Cache sDestination) = 0;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) = 0;
		void computeForward(CacheContainer::CacheInfo *pDestination);
		void computeBackward(CacheContainer::CacheInfo *pDestination, CacheContainer::CacheInfo *pTemporary);
	};

	inline const std::string &GraphNode::name() const
	{
		return this->sName;
	}

	inline std::size_t GraphNode::forwardNodeCount() const
	{
		return this->sForwardList.size();
	}

	inline std::size_t GraphNode::backwardNodeCount() const
	{
		return this->sBackwardList.size();
	}

	inline bool GraphNode::isLeafForward() const
	{
		return !this->forwardNodeCount();
	}

	inline bool GraphNode::isLeafBackward() const
	{
		return !this->backwardNodeCount();
	}
}

#endif

/*
	2018.05.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_GRAPH_H

#define _CLASS_TINNET_GRAPH_GRAPH_H

#include "../TinNetDLL.h"

#include "CacheContainer.h"
#include "GraphBP.h"
#include "GraphNode.h"
#include "GraphNodeBP.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace TinNet::Graph
{
	class TINNET_DLL Graph final
	{
	private:
		CacheContainer sCacheContainer;
		std::unordered_map<std::string, std::unique_ptr<GraphNode>> sGraphNodeMap;

	public:
		Graph(const GraphBP &sGraphBP);
		Graph(const Graph &sSrc) = delete;
		Graph(Graph &&sSrc) = default;
		~Graph();

	public:
		Graph &operator=(const Graph &sSrc) = delete;
		Graph &operator=(Graph &&sSrc) = default;

	public:
		inline CacheContainer &cacheContainer();
		inline const CacheContainer &cacheContainer() const;
		inline GraphNode *node(const std::string &sNodeName);
		inline const GraphNode *node(const std::string &sNodeName) const;
		template<class T> inline T *node(const std::string &sNodeName);
		template<class T> inline const T *node(const std::string &sNodeName) const;
		void enableBackward();
		void disableBackward();
		const Cache *forward(GraphNode *pNode);
		const Cache *forward(const std::string &sNodeName);
		const Cache *backward(GraphNode *pNode);
		const Cache *backward(const std::string &sNodeName);
		Cache &input(const std::string &sInputName);
		const Cache &input(const std::string &sInputName) const;
	};

	inline CacheContainer &Graph::cacheContainer()
	{
		return this->sCacheContainer;
	}

	inline const CacheContainer &Graph::cacheContainer() const
	{
		return this->sCacheContainer;
	}

	inline GraphNode *Graph::node(const std::string &sNodeName)
	{
		auto iIndex{this->sGraphNodeMap.find(sNodeName)};

		return iIndex == this->sGraphNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	inline const GraphNode *Graph::node(const std::string &sNodeName) const
	{
		auto iIndex{this->sGraphNodeMap.find(sNodeName)};

		return iIndex == this->sGraphNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	template<class T> inline T *Graph::node(const std::string &sNodeName)
	{
		auto iIndex{this->sGraphNodeMap.find(sNodeName)};

		return iIndex == this->sGraphNodeMap.cend() ? nullptr : static_cast<T *>(iIndex->second.get());
	}

	template<class T> inline const T *Graph::node(const std::string &sNodeName) const
	{
		auto iIndex{this->sGraphNodeMap.find(sNodeName)};

		return iIndex == this->sGraphNodeMap.cend() ? nullptr : static_cast<const T *>(iIndex->second.get());
	}
}

#endif
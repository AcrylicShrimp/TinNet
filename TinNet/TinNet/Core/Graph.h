
/*
	2019.03.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_GRAPH_H

#define _CLASS_TINNET_CORE_GRAPH_H

#include "../TinNetDLL.h"

#include "GraphBuilder.h"
#include "NodeWrapper.h"

#include "../Node/Node.h"
#include "../Node/NodeType.h"
#include "../Node/NodeTypeManager.h"

#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace TinNet::Core
{
	class TINNET_DLL Graph final
	{
	public:
		Node::NodeTypeManager sNodeTypeManager;

	private:
		GraphBuilder sBuilder;
		std::unordered_map<std::string, std::unique_ptr<Node::Node>> sNodeMap;
		std::unordered_multimap<const Node::NodeType *, Node::Node *> sNodeTypeMap;

	public:
		Graph();
		Graph(const Graph &sSrc) = delete;
		~Graph() noexcept = default;

	public:
		Graph &operator=(const Graph &sSrc) = delete;
		inline NodeWrapper operator[](const std::string &sNodeName) const;

	public:
		inline GraphBuilder &builder() noexcept;
		std::vector<Node::Node *> nodes(const Node::NodeType *pNodeType);
		std::vector<const Node::Node *> nodes(const Node::NodeType *pNodeType) const;
		inline std::size_t nodeCount(const Node::NodeType *pNodeType) const;
		inline Node::Node *node(const std::string &sNodeName);
		inline const Node::Node *node(const std::string &sNodeName) const;
		inline std::vector<Node::Node *> nodes();
		inline std::vector<const Node::Node *> nodes() const;
		template<class T> std::size_t nodeCount() const;
		template<class T> T *node(const std::string &sNodeName);
		template<class T> const T *node(const std::string &sNodeName) const;
		template<class T> std::vector<T *> nodes();
		template<class T> std::vector<const T *> nodes() const;
		template<class T, class ...P> T *createNode(const std::string &sNodeName, P &&...tParam);
	};

	inline NodeWrapper Graph::operator[](const std::string &sNodeName) const
	{
		return NodeWrapper{this->sNodeMap.find(sNodeName)->second.get()};
	}

	inline GraphBuilder &Graph::builder() noexcept
	{
		return this->sBuilder;
	}

	inline std::size_t Graph::nodeCount(const Node::NodeType *pNodeType) const
	{
		return this->sNodeTypeMap.count(pNodeType);
	}

	inline Node::Node *Graph::node(const std::string &sNodeName)
	{
		auto iIndex{this->sNodeMap.find(sNodeName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	inline const Node::Node *Graph::node(const std::string &sNodeName) const
	{
		auto iIndex{this->sNodeMap.find(sNodeName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	inline std::vector<Node::Node *> Graph::nodes()
	{
		return this->nodes<Node::Node>();
	}

	inline std::vector<const Node::Node *> Graph::nodes() const
	{
		return this->nodes<Node::Node>();
	}
}

#include "Graph.hpp"

#endif
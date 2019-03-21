
/*
	2019.03.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_GRAPH_H

#define _CLASS_TINNET_CORE_GRAPH_H

#include "../TinNetDLL.h"

#include "../Node/Node.h"
#include "../Node/NodeType.h"
#include "../Node/NodeTypeManager.h"

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace TinNet::Core
{
	/// fdsfdafsd
	class TINNET_DLL Graph final
	{
	public:
		Node::NodeTypeManager sNodeTypeManager;

	private:
		std::unordered_map<std::string, std::unique_ptr<Node::Node>> sNodeMap;

	public:
		Graph() = default;
		Graph(const Graph &sSrc) = delete;
		~Graph() noexcept = default;

	public:
		Graph &operator=(const Graph &sSrc) = delete;
		inline Node::Node &operator[](const std::string &sNodeName);
		inline const Node::Node &operator[](const std::string &sNodeName) const;

	public:
		inline Node::Node *node(const std::string &sNodeName);
		inline const Node::Node *node(const std::string &sNodeName) const;
		template<class T> inline T *node(const std::string &sNodeName);
		template<class T> inline const T *node(const std::string &sNodeName) const;
		template<class T, class ...P> inline T *createNode(const std::string &sNodeName, P &&...tParam);
	};

	inline Node::Node &Graph::operator[](const std::string &sNodeName)
	{
		return *this->sNodeMap.find(sNodeName)->second.get();
	}

	inline const Node::Node &Graph::operator[](const std::string &sNodeName) const
	{
		return *this->sNodeMap.find(sNodeName)->second.get();
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

	template<class T> inline T *Graph::node(const std::string &sNodeName)
	{
		static_assert(std::is_base_of<Node::Node, T>());

		auto *pNode{this->node(sNodeName)};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType->isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<T *>(pNode);
	}

	template<class T> inline const T *Graph::node(const std::string &sNodeName) const
	{
		static_assert(std::is_base_of<Node::Node, T>());

		const auto *pNode{this->node(sNodeName)};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType->isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<const T *>(pNode);
	}

	template<class T, class ...P> inline T *Graph::createNode(const std::string &sNodeName, P &&...tParam)
	{
		static_assert(std::is_base_of<Node::Node, T>());

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType)
			return false;

		auto *pNode{this->node(sNodeName)};

		if (!pNode)
			pNode = this->sNodeMap.emplace(std::piecewise_construct, std::forward_as_tuple(sNodeName), std::forward_as_tuple(new T(this, sNodeName, std::forward<P>(tParam)...))).first->second.get();

		if (!pNodeType->isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<T *>(pNode);
	}
}

#endif
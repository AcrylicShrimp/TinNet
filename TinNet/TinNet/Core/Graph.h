
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

#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

namespace TinNet::Core
{
	class TINNET_DLL Graph final
	{
	private:
		Node::NodeTypeManager sNodeTypeManager;
		std::unordered_map<std::string, Node::Node> sNodeMap;

	public:
		Graph() = default;
		Graph(const Graph &sSrc) = delete;
		~Graph() noexcept = default;

	public:
		Graph &operator=(const Graph &sSrc) = delete;
		inline Node::Node *operator[](const std::string &sNodeName);
		inline const Node::Node *operator[](const std::string &sNodeName) const;

	public:
		inline const Node::NodeTypeManager &nodeTypeManager() const;
		template<class T> inline T *node(const std::string &sNodeName);
		template<class T> inline const T *node(const std::string &sNodeName) const;
	};

	inline Node::Node *Graph::operator[](const std::string &sNodeName)
	{
		auto iIndex{this->sNodeMap.find(sNodeName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : &iIndex->second;
	}

	inline const Node::Node *Graph::operator[](const std::string &sNodeName) const
	{
		auto iIndex{this->sNodeMap.find(sNodeName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : &iIndex->second;
	}

	inline const Node::NodeTypeManager &Graph::nodeTypeManager() const
	{
		return this->sNodeTypeManager;
	}

	template<class T> inline T *Graph::node(const std::string &sNodeName)
	{
		static_assert(std::is_base_of<Node::Node, T>());

		auto *pNode{(*this)[sNodeName]};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType.isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<T *>(pNode);
	}

	template<class T> inline const T *Graph::node(const std::string &sNodeName) const
	{
		static_assert(std::is_base_of<Node::Node, T>());

		const auto *pNode{(*this)[sNodeName]};

		if (!pNode)
			return nullptr;

		const auto *pNodeType{this->sNodeTypeManager.type<T>()};

		if (!pNodeType || !pNodeType.isBaseOf(pNode->type()))
			return nullptr;

		return static_cast<const T *>(pNode);
	}
}

#endif
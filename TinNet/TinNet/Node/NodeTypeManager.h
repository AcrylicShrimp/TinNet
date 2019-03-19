
/*
	2019.03.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_NODETYPEMANAGER_H

#define _CLASS_TINNET_NODE_NODETYPEMANAGER_H

#include "../TinNetDLL.h"

#include "Node.h"
#include "NodeType.h"

#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace TinNet::Node
{
	class TINNET_DLL NodeTypeManager final
	{
	private:
		std::unordered_map<std::string, NodeType> sNodeTypeMap;

	public:
		NodeTypeManager() = default;
		NodeTypeManager(const NodeTypeManager &sSrc) = delete;
		~NodeTypeManager() noexcept = default;

	public:
		NodeTypeManager &operator=(const NodeTypeManager &sSrc) = delete;

	public:
		inline const NodeType *type(const std::string &sTypeName) const;
		template<class T> inline const NodeType *type() const;
		template<class T> inline void registerNode();
		template<class T, class B> inline void registerNode();
	};

	inline const NodeType *NodeTypeManager::type(const std::string &sTypeName) const
	{
		auto iIndex{this->sNodeTypeMap.find(sTypeName)};

		return iIndex == this->sNodeTypeMap.cend() ? nullptr : &iIndex->second;
	}

	template<class T> inline const NodeType *NodeTypeManager::type() const
	{
		static_assert(std::is_base_of<Node, T>());

		return this->type(T::typeName());
	}

	template<class T> inline void NodeTypeManager::registerNode()
	{
		static_assert(std::is_base_of<Node, T>());

		this->registerNode<T, Node>();
	}

	template<class T, class B> inline void NodeTypeManager::registerNode()
	{
		static_assert(std::is_base_of<B, T>());
		static_assert(std::is_base_of<Node, B>());

		if (this->type<T>())
			throw std::exception{"already registered node type."};

		const auto *pBaseType{this->type<B>()};

		if (!pBaseType)
			throw std::exception{"base type not registered."};

		auto sTypeName{T::typeName()};

		this->sNodeTypeMap.emplace(std::piecewise_construct, std::forward_as_tuple(sTypeName), std::forward_as_tuple(pBaseType, sTypeName));
	}
}

#endif
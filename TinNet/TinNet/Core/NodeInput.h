
/*
	2019.01.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_NODEINPUT_H

#define _CLASS_TINNET_CORE_NODEINPUT_H

#include "../TinNetDLL.h"

#include "Shape.h"
#include "Span.h"

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_set>

namespace TinNet::Core
{
	class Node;

	class TINNET_DLL NodeInput final
	{
	public:
		Node *const pNode;
		const std::string sName;
		const std::function<Span(const Node *)> fBackwardOp;

	protected:
		Node *pInputNode;
		std::unordered_set<Node *> sDepsSet;
		
	public:
		NodeInput(Node *pNode, std::string_view sName, const std::function<Span(const Node *)> &fBackwardOp);
		NodeInput(const NodeInput &sSrc) = default;
		NodeInput(NodeInput &&sSrc) noexcept = default;
		~NodeInput() noexcept = default;
		
	public:
		NodeInput &operator=(const NodeInput &sSrc) = default;
		NodeInput &operator=(NodeInput &&sSrc) noexcept = default;
		
	public:
		inline Node *inputNode() noexcept;
		inline const Node *inputNode() const noexcept;
		inline bool dependOn(const Node *pNode) const;
		void attach(Node *pInputNode);
	};

	inline Node *NodeInput::inputNode()
	{
		return this->pInputNode;
	}

	inline const Node *NodeInput::inputNode() const
	{
		return this->pInputNode;
	}

	inline bool NodeInput::dependOn(const Node *pNode) const
	{
		return this->sDepsSet.count(const_cast<Node *>(pNode));
	}
}

#endif
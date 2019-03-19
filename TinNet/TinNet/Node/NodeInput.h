
/*
	2019.01.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_NODEINPUT_H

#define _CLASS_TINNET_NODE_NODEINPUT_H

#include "../TinNetDLL.h"

#include "../Core/Shape.h"
#include "../Core/Span.h"

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_set>

namespace TinNet::Node
{
	class Node;

	class TINNET_DLL NodeInput final
	{
	public:
		Node *const pNode;
		const std::string sName;
		const std::function<void (const Node *)> fBackwardOp;

	protected:
		Node *pInputNode;
		std::unordered_set<Node *> sDepsSet;
		
	public:
		NodeInput(Node *pNode, std::string_view sName, const std::function<void (const Node *)> &fBackwardOp);
		NodeInput(const NodeInput &sSrc) = default;
		NodeInput(NodeInput &&sSrc) noexcept = default;
		~NodeInput() noexcept = default;
		
	public:
		NodeInput &operator=(const NodeInput &sSrc) = default;
		NodeInput &operator=(NodeInput &&sSrc) noexcept = default;
		
	public:
		inline Node *inputNode() noexcept;
		inline const Node *inputNode() const noexcept;
		inline bool isDependOn(const Node *pNode) const;
		void attach(Node *pInputNode);
	};

	inline Node *NodeInput::inputNode() noexcept
	{
		return this->pInputNode;
	}

	inline const Node *NodeInput::inputNode() const noexcept
	{
		return this->pInputNode;
	}

	inline bool NodeInput::isDependOn(const Node *pNode) const
	{
		return this->sDepsSet.count(const_cast<Node *>(pNode));
	}
}

#endif
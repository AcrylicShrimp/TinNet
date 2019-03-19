
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_NODE_H

#define _CLASS_TINNET_NODE_NODE_H

#include "../TinNetDLL.h"

#include "../Core/Memory.h"
#include "../Core/Span.h"

#include "NodeInput.h"
#include "NodeType.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define TINNET_NODE_TYPE_DCL(TYPENAME)								\
public:																\
	virtual const NodeType *type() const override;					\
	inline static std::string_view typeName()						\
	{																\
		return #TYPENAME;											\
	}

#define TINNET_NODE_TYPE_DEF(CLASS)									\
	const NodeType *CLASS::type() const								\
	{																\
		return this->pGraph->nodeTypeManager().type<CLASS>();		\
	}

namespace TinNet::Core
{
	class Graph;
}

namespace TinNet::Node
{
	class TINNET_DLL Node
	{
	public:
		friend NodeInput;

	public:
		Core::Graph const *pGraph;
		const std::string sName;

	private:
		bool bShapeDirty;
		bool bOutputDirty;
		const Node *pGradientDirty;

	protected:
		Core::Shape sShape;
		Core::Memory sOutput;
		Core::Memory sGradient;
		std::vector<NodeInput *> sRevNodeInputList;
		std::unordered_set<Node *> sDeps;
		std::unordered_set<Node *> sRevDeps;
		std::unordered_map<std::string, NodeInput *> sNodeInputMap;

	protected:
		Node(Core::Graph *pGraph, std::string_view sName);

	public:
		Node(const Node &sSrc) = delete;
		virtual ~Node() noexcept = default;

	public:
		Node &operator=(const Node &sSrc) = delete;
		NodeInput *operator[](std::string_view sNodeInputName);
		const NodeInput *operator[](std::string_view sNodeInputName) const;

	public:
		inline const Core::Shape &shape() const noexcept;
		inline Core::Span output() const noexcept;
		inline Core::Span gradient() const noexcept;
		inline bool hasDeps(const Node *pNode) const;
		inline bool hasRevDeps(const Node *pNode) const;
		Node &markDirty();
		Node &evalShape();
		Node &evalOutput();
		Node &evalGradient(const Node *pDy);
		virtual const NodeType *type() const;
		inline static std::string_view typeName()
		{
			return "node";
		}

	protected:
		virtual void __evaluateShape() = 0;
		virtual void __evaluateOutput() = 0;
	};

	inline const Core::Shape &Node::shape() const noexcept
	{
		return this->sShape;
	}

	inline Core::Span Node::output() const noexcept
	{
		return this->sOutput.span();
	}

	inline Core::Span Node::gradient() const noexcept
	{
		return this->sGradient.span();
	}

	inline bool Node::hasDeps(const Node *pNode) const
	{
		return this->sDeps.count(const_cast<Node *>(pNode));
	}

	inline bool Node::hasRevDeps(const Node *pNode) const
	{
		return this->sRevDeps.count(const_cast<Node *>(pNode));
	}
}

#endif
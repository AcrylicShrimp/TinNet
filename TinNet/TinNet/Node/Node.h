
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_NODE_H

#define _CLASS_TINNET_CORE_NODE_H

#include "../TinNetDLL.h"

#include "../Core/Memory.h"
#include "../Core/Span.h"

#include "NodeInput.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace TinNet::Node
{
	//class Graph;

	class TINNET_DLL Node
	{
	public:
		//friend Graph;
		friend NodeInput;

	public:
		//Graph *const pGraph;
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
		//Node(Graph *pGraph, std::string_view sName);
		Node(std::string_view sName);

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
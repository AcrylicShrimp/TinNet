
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_H

#define _CLASS_TINNET_NODE_H

#include "TinNetDLL.h"

#include "Shape.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace TinNet
{
	using NodePtr = class Node *;
	using NodeRef = class Node &;

	class TINNET_DLL Node
	{
	protected:
		class Graph *pGraph;
		std::string sName;
		std::vector<NodePtr> sInputList;
		std::vector<NodePtr> sOutputList;

	public:
		Node(Graph *pGraph, const std::string &sName);
		Node(const Node &sSrc) = delete;
		virtual ~Node() = default;
		
	public:
		Node &operator=(const Node &sSrc) = delete;
		
	public:
		virtual Shape shape() const = 0;
		virtual std::string type() const = 0;
		virtual void notifyShapeUpdated() = 0;
		virtual void notifyBackwardEnabled() = 0;
		virtual void notifyBackwardDisabled() = 0;
		virtual Cache forward() = 0;
		virtual Cache backward() = 0;
		virtual void beginGradient() = 0;
		inline class Graph *graph();
		inline const class Graph *graph() const;
		inline const std::string &name() const;
		inline std::size_t inputCount() const;
		inline std::size_t outputCount() const;
		inline bool isLeafInput() const;
		inline bool isLeafOutput() const;
		static void link(NodePtr pInput, NodePtr pOutput);
		static void unlink(NodePtr pInput, NodePtr pOutput);

	protected:
		virtual void forwardPass(Cache sDestination) = 0;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) = 0;
		void computeForward(CachePtr pDestination);
		void computeBackward(CachePtr pDestination);
	};

	inline class Graph *Node::graph()
	{
		return this->pGraph;
	}

	inline const class Graph *Node::graph() const
	{
		return this->pGraph;
	}

	inline const std::string &Node::name() const
	{
		return this->sName;
	}

	inline std::size_t Node::inputCount() const
	{
		return this->sInputList.size();
	}

	inline std::size_t Node::outputCount() const
	{
		return this->sOutputList.size();
	}

	inline bool Node::isLeafInput() const
	{
		return this->sInputList.empty();
	}

	inline bool Node::isLeafOutput() const
	{
		return this->sOutputList.empty();
	}
}

#endif
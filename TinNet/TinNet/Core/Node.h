
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_NODE_H

#define _CLASS_TINNET_CORE_NODE_H

#include "../TinNetDLL.h"

#include "Span.h"		//TinNet::Core::Span

#include <vector>		//std::vector

namespace TinNet::Core
{
	class TINNET_DLL Node
	{
	protected:
		std::vector<Node *> sOut;
		
	public:
		Node();
		Node(const Node &sSrc) = delete;
		virtual ~Node() noexcept = default;
		
	public:
		Node &operator=(const Node &sSrc) = delete;
		
	public:
		inline const std::vector<Node *> &out() const noexcept;
		Span forward();
		Span backward();
		static void connect(Node *pFrom, Node *pTo);
		static void disconnect(Node *pFrom, Node *pTo);

	protected:
		virtual Span calcForward() = 0;
		virtual Span calcBackward() = 0;
	};

	inline const std::vector<Node *> &Node::out() const noexcept
	{
		return this->sOut;
	}
}

#endif